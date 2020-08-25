/**
 *
 *  MysqlConnection.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 *
 */

#pragma once

#include "../DbConnection.h"
#include <trantor/net/EventLoop.h>
#include <trantor/net/inner/Channel.h>
#include <drogon/orm/DbClient.h>
#include <trantor/utils/NonCopyable.h>
#include <mysql.h>
#include <memory>
#include <string>
#include <functional>
#include <iostream>

namespace drogon
{
namespace orm
{

class MysqlConnection;
typedef std::shared_ptr<MysqlConnection> MysqlConnectionPtr;
class MysqlConnection : public DbConnection, public std::enable_shared_from_this<MysqlConnection>
{
  public:
    MysqlConnection(trantor::EventLoop *loop, const std::string &connInfo);
    ~MysqlConnection() { }
    virtual void execSql(const std::string &sql,
                         size_t paraNum,
                         const std::vector<const char *> &parameters,
                         const std::vector<int> &length,
                         const std::vector<int> &format,
                         const ResultCallback &rcb,
                         const std::function<void(const std::exception_ptr &)> &exceptCallback,
                         const std::function<void()> &idleCb) override;

  private:
    std::unique_ptr<trantor::Channel> _channelPtr;
    std::shared_ptr<MYSQL> _mysqlPtr;
   
    void handleTimeout();
   
    void handleClosed();
    void handleEvent();
    void setChannel();
    void getResult(MYSQL_RES *res);
    void getStmtResult();
    int _waitStatus;
    enum ExecStatus
    {
      ExecStatus_None = 0,
      ExecStatus_RealQuery,
      ExecStatus_StmtPrepare,
      ExecStatus_StoreResult,
      ExecStatus_StmtExec,
      ExecStatus_StmtStoreResult
    };
    ExecStatus _execStatus = ExecStatus_None;
    std::shared_ptr<MYSQL_STMT> _stmtPtr;

    void outputError();
    void outputStmtError();
    std::vector<MYSQL_BIND>
        _binds;
    std::vector<unsigned long> _lengths;
    std::vector<my_bool> _isNulls;
};

} // namespace orm
} // namespace drogon