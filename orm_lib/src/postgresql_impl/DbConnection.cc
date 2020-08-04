#include "DbConnection.h"
#include "PostgreSQLResultImpl.h"
#include <drogon/orm/Exception.h>
#include <stdio.h>

using namespace drogon::orm;
namespace drogon
{
namespace orm
{

Result makeResult(const std::shared_ptr<PGresult> &r = std::shared_ptr<PGresult>(nullptr), const std::string &query = "")
{
    return Result(std::shared_ptr<PostgreSQLResultImpl>(new PostgreSQLResultImpl(r, query)));
}

} // namespace orm
} // namespace drogon

DbConnection::DbConnection(trantor::EventLoop *loop, const std::string &connInfo)
    : _connPtr(std::shared_ptr<PGconn>(PQconnectStart(connInfo.c_str()), [](PGconn *conn) {
          PQfinish(conn);
      })),
      _loop(loop), _channel(_loop, PQsocket(_connPtr.get()))
{
    //std::cout<<"sock="<<sock()<<std::endl;
    _channel.setReadCallback([=]() {
        //std::cout<<"reading callback"<<std::endl;
        if (_status != ConnectStatus_Ok)
        {
            pgPoll();
        }
        else
        {
            handleRead();
        }
    });
    _channel.setWriteCallback([=]() {
        //std::cout<<"writing callback"<<std::endl;
        if (_status != ConnectStatus_Ok)
        {
            pgPoll();
        }
        else
        {
            PQconsumeInput(_connPtr.get());
        }
    });
    _channel.setCloseCallback([=]() {
        perror("sock close");
        handleClosed();
    });
    _channel.setErrorCallback([=]() {
        perror("sock err");
        handleClosed();
    });
    _channel.enableReading();
    _channel.enableWriting();
}
int DbConnection::sock()
{
    return PQsocket(_connPtr.get());
}
void DbConnection::handleClosed()
{
    std::cout << "handleClosed!" << this << std::endl;
    _loop->assertInLoopThread();
    _channel.disableAll();
    _channel.remove();
    assert(_closeCb);
    auto thisPtr = shared_from_this();
    _closeCb(thisPtr);
}
void DbConnection::pgPoll()
{
    _loop->assertInLoopThread();
    auto connStatus = PQconnectPoll(_connPtr.get());

    switch (connStatus)
    {
    case PGRES_POLLING_FAILED:
        /*            fprintf(stderr, "!!!Pg connection failed: %s",
                    PQerrorMessage(_connPtr.get()));
            if(_isWorking){
                _isWorking=false;
                auto r=makeResult(SqlStatus::NetworkError, nullptr,_sql);
                r.setError(PQerrorMessage(_connPtr.get()));
                assert(_cb);
                _cb(r);
            }
            handleClosed();
*/
        fprintf(stderr, "!!!Pg connection failed: %s",
                PQerrorMessage(_connPtr.get()));

        break;
    case PGRES_POLLING_WRITING:
        _channel.enableWriting();
        _channel.disableReading();
        break;
    case PGRES_POLLING_READING:
        _channel.enableReading();
        _channel.disableWriting();
        break;

    case PGRES_POLLING_OK:
        if (_status != ConnectStatus_Ok)
        {
            _status = ConnectStatus_Ok;
            assert(_okCb);
            _okCb(shared_from_this());
        }
        _channel.enableReading();
        _channel.disableWriting();
        break;
    case PGRES_POLLING_ACTIVE:
        //unused!
        printf("active\n");
        break;
    default:
        break;
    }
}
void DbConnection::execSql(const std::string &sql,
                           size_t paraNum,
                           const std::vector<const char *> &parameters,
                           const std::vector<int> &length,
                           const std::vector<int> &format,
                           const ResultCallback &rcb,
                           const std::function<void(const std::exception_ptr &)> &exceptCallback,
                           const std::function<void()> &idleCb)
{
    assert(paraNum == parameters.size());
    assert(paraNum == length.size());
    assert(paraNum == format.size());
    assert(rcb);
    assert(idleCb);
    assert(!_isWorking);
    assert(!sql.empty());
    _sql = sql;
    _cb = rcb;
    _idleCb = idleCb;
    _isWorking = true;
    _exceptCb = exceptCallback;
    //_channel.enableWriting();
    LOG_TRACE << sql;
    if (PQsendQueryParams(
            _connPtr.get(),
            sql.c_str(),
            paraNum,
            NULL,
            parameters.data(),
            length.data(),
            format.data(),
            0) == 0)
    {
        fprintf(stderr, "send query error:%s\n", PQerrorMessage(_connPtr.get()));
        //FIXME call exception callback
    }
    auto thisPtr = shared_from_this();
    _loop->runInLoop([=]() {
        thisPtr->pgPoll();
    });
}
void DbConnection::handleRead()
{

    std::shared_ptr<PGresult> res;

    if (!PQconsumeInput(_connPtr.get()))
    {
        fprintf(stderr, "Failed to consume pg input: %s\n",
                PQerrorMessage(_connPtr.get()));
        if (_isWorking)
        {
            _isWorking = false;
            try
            {
                throw BrokenConnection(PQerrorMessage(_connPtr.get()));
            }
            catch (...)
            {
                auto exceptPtr = std::current_exception();
                _exceptCb(exceptPtr);
                _exceptCb = decltype(_exceptCb)();
            }
            _cb = decltype(_cb)();
        }
        handleClosed();
        return;
    }

    if (PQisBusy(_connPtr.get()))
    {
        //need read more data from socket;
        printf("need read more data from socket!\n");
        return;
    }

    _channel.disableWriting();
    // got query results?
    while ((res = std::shared_ptr<PGresult>(PQgetResult(_connPtr.get()), [](PGresult *p) {
                PQclear(p);
            })))
    {
        auto type = PQresultStatus(res.get());
        if (type == PGRES_BAD_RESPONSE || type == PGRES_FATAL_ERROR)
        {
            fprintf(stderr, "Result error: %s", PQerrorMessage(_connPtr.get()));
            if (_isWorking)
            {
                {
                    try
                    {
                        //FIXME exception type
                        throw SqlError(PQerrorMessage(_connPtr.get()),
                                       _sql);
                    }
                    catch (...)
                    {
                        _exceptCb(std::current_exception());
                        _exceptCb = decltype(_exceptCb)();
                    }
                }
                _cb = decltype(_cb)();
            }
        }
        else
        {
            if (_isWorking)
            {
                auto r = makeResult(res, _sql);
                _cb(r);
                _cb = decltype(_cb)();
                _exceptCb = decltype(_exceptCb)();
            }
        }
    }
    if (_isWorking)
    {
        _isWorking = false;
        _idleCb();
    }
}
