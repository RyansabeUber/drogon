/**
 *
 *  Users.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Users.h"
#include <trantor/utils/config.h>
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon_model::postgres;

const std::string Users::Cols::user_id = "user_id";
const std::string Users::Cols::user_name = "user_name";
const std::string Users::Cols::password = "password";
const std::string Users::Cols::org_name = "org_name";
const std::string Users::Cols::signature = "signature";
const std::string Users::Cols::avatar_id = "avatar_id";
const std::string Users::Cols::id = "id";
const std::string Users::Cols::salt = "salt";
const std::string Users::Cols::admin = "admin";
const std::string Users::primaryKeyName = "id";
const bool Users::hasPrimaryKey = true;
const std::string Users::tableName = "users";

const std::vector<typename Users::MetaData> Users::_metaData={
{"user_id","std::string","character varying",32,0,0,0},
{"user_name","std::string","character varying",64,0,0,0},
{"password","std::string","character varying",64,0,0,0},
{"org_name","std::string","character varying",20,0,0,0},
{"signature","std::string","character varying",50,0,0,0},
{"avatar_id","std::string","character varying",32,0,0,0},
{"id","int32_t","integer",4,1,1,1},
{"salt","std::string","character varying",20,0,0,0},
{"admin","bool","boolean",1,0,0,0}
};
const std::string &Users::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
Users::Users(const Row &r) noexcept
{
        if(!r["user_id"].isNull())
        {
            _userId=std::make_shared<std::string>(r["user_id"].as<std::string>());
        }
        if(!r["user_name"].isNull())
        {
            _userName=std::make_shared<std::string>(r["user_name"].as<std::string>());
        }
        if(!r["password"].isNull())
        {
            _password=std::make_shared<std::string>(r["password"].as<std::string>());
        }
        if(!r["org_name"].isNull())
        {
            _orgName=std::make_shared<std::string>(r["org_name"].as<std::string>());
        }
        if(!r["signature"].isNull())
        {
            _signature=std::make_shared<std::string>(r["signature"].as<std::string>());
        }
        if(!r["avatar_id"].isNull())
        {
            _avatarId=std::make_shared<std::string>(r["avatar_id"].as<std::string>());
        }
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["salt"].isNull())
        {
            _salt=std::make_shared<std::string>(r["salt"].as<std::string>());
        }
        if(!r["admin"].isNull())
        {
            _admin=std::make_shared<bool>(r["admin"].as<bool>());
        }
}
const std::string & Users::getValueOfUserId(const std::string &defaultValue) const noexcept
{
    if(_userId)
        return *_userId;
    return defaultValue;
}
std::shared_ptr<const std::string> Users::getUserId() const noexcept
{
    return _userId;
}
void Users::setUserId(const std::string &userId) noexcept
{
    _userId = std::make_shared<std::string>(userId);
    _dirtyFlag[0] = true;
}
void Users::setUserId(std::string &&userId) noexcept
{
    _userId = std::make_shared<std::string>(std::move(userId));
    _dirtyFlag[0] = true;
}


const std::string & Users::getValueOfUserName(const std::string &defaultValue) const noexcept
{
    if(_userName)
        return *_userName;
    return defaultValue;
}
std::shared_ptr<const std::string> Users::getUserName() const noexcept
{
    return _userName;
}
void Users::setUserName(const std::string &userName) noexcept
{
    _userName = std::make_shared<std::string>(userName);
    _dirtyFlag[1] = true;
}
void Users::setUserName(std::string &&userName) noexcept
{
    _userName = std::make_shared<std::string>(std::move(userName));
    _dirtyFlag[1] = true;
}


const std::string & Users::getValueOfPassword(const std::string &defaultValue) const noexcept
{
    if(_password)
        return *_password;
    return defaultValue;
}
std::shared_ptr<const std::string> Users::getPassword() const noexcept
{
    return _password;
}
void Users::setPassword(const std::string &password) noexcept
{
    _password = std::make_shared<std::string>(password);
    _dirtyFlag[2] = true;
}
void Users::setPassword(std::string &&password) noexcept
{
    _password = std::make_shared<std::string>(std::move(password));
    _dirtyFlag[2] = true;
}


const std::string & Users::getValueOfOrgName(const std::string &defaultValue) const noexcept
{
    if(_orgName)
        return *_orgName;
    return defaultValue;
}
std::shared_ptr<const std::string> Users::getOrgName() const noexcept
{
    return _orgName;
}
void Users::setOrgName(const std::string &orgName) noexcept
{
    _orgName = std::make_shared<std::string>(orgName);
    _dirtyFlag[3] = true;
}
void Users::setOrgName(std::string &&orgName) noexcept
{
    _orgName = std::make_shared<std::string>(std::move(orgName));
    _dirtyFlag[3] = true;
}


const std::string & Users::getValueOfSignature(const std::string &defaultValue) const noexcept
{
    if(_signature)
        return *_signature;
    return defaultValue;
}
std::shared_ptr<const std::string> Users::getSignature() const noexcept
{
    return _signature;
}
void Users::setSignature(const std::string &signature) noexcept
{
    _signature = std::make_shared<std::string>(signature);
    _dirtyFlag[4] = true;
}
void Users::setSignature(std::string &&signature) noexcept
{
    _signature = std::make_shared<std::string>(std::move(signature));
    _dirtyFlag[4] = true;
}


const std::string & Users::getValueOfAvatarId(const std::string &defaultValue) const noexcept
{
    if(_avatarId)
        return *_avatarId;
    return defaultValue;
}
std::shared_ptr<const std::string> Users::getAvatarId() const noexcept
{
    return _avatarId;
}
void Users::setAvatarId(const std::string &avatarId) noexcept
{
    _avatarId = std::make_shared<std::string>(avatarId);
    _dirtyFlag[5] = true;
}
void Users::setAvatarId(std::string &&avatarId) noexcept
{
    _avatarId = std::make_shared<std::string>(std::move(avatarId));
    _dirtyFlag[5] = true;
}


const int32_t & Users::getValueOfId(const int32_t &defaultValue) const noexcept
{
    if(_id)
        return *_id;
    return defaultValue;
}
std::shared_ptr<const int32_t> Users::getId() const noexcept
{
    return _id;
}
const typename Users::PrimaryKeyType & Users::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const std::string & Users::getValueOfSalt(const std::string &defaultValue) const noexcept
{
    if(_salt)
        return *_salt;
    return defaultValue;
}
std::shared_ptr<const std::string> Users::getSalt() const noexcept
{
    return _salt;
}
void Users::setSalt(const std::string &salt) noexcept
{
    _salt = std::make_shared<std::string>(salt);
    _dirtyFlag[7] = true;
}
void Users::setSalt(std::string &&salt) noexcept
{
    _salt = std::make_shared<std::string>(std::move(salt));
    _dirtyFlag[7] = true;
}


const bool & Users::getValueOfAdmin(const bool &defaultValue) const noexcept
{
    if(_admin)
        return *_admin;
    return defaultValue;
}
std::shared_ptr<const bool> Users::getAdmin() const noexcept
{
    return _admin;
}
void Users::setAdmin(const bool &admin) noexcept
{
    _admin = std::make_shared<bool>(admin);
    _dirtyFlag[8] = true;
}


void Users::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Users::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "user_id",
        "user_name",
        "password",
        "org_name",
        "signature",
        "avatar_id",
        "salt",
        "admin"
    };
    return _inCols;
}

void Users::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getUserId())
    {
        binder << getValueOfUserId();
    }
    else
    {
        binder << nullptr;
    }
    if(getUserName())
    {
        binder << getValueOfUserName();
    }
    else
    {
        binder << nullptr;
    }
    if(getPassword())
    {
        binder << getValueOfPassword();
    }
    else
    {
        binder << nullptr;
    }
    if(getOrgName())
    {
        binder << getValueOfOrgName();
    }
    else
    {
        binder << nullptr;
    }
    if(getSignature())
    {
        binder << getValueOfSignature();
    }
    else
    {
        binder << nullptr;
    }
    if(getAvatarId())
    {
        binder << getValueOfAvatarId();
    }
    else
    {
        binder << nullptr;
    }
    if(getSalt())
    {
        binder << getValueOfSalt();
    }
    else
    {
        binder << nullptr;
    }
    if(getAdmin())
    {
        binder << getValueOfAdmin();
    }
    else
    {
        binder << nullptr;
    }
}

const std::vector<std::string> Users::updateColumns() const
{
    std::vector<std::string> ret;
    for(size_t i=0;i<sizeof(_dirtyFlag);i++)
    {
        if(_dirtyFlag[i])
        {
            ret.push_back(getColumnName(i));
        }
    }
    return ret;
}

void Users::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[0])
    {
        if(getUserId())
        {
            binder << getValueOfUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[1])
    {
        if(getUserName())
        {
            binder << getValueOfUserName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getPassword())
        {
            binder << getValueOfPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getOrgName())
        {
            binder << getValueOfOrgName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
    {
        if(getSignature())
        {
            binder << getValueOfSignature();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[5])
    {
        if(getAvatarId())
        {
            binder << getValueOfAvatarId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[7])
    {
        if(getSalt())
        {
            binder << getValueOfSalt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[8])
    {
        if(getAdmin())
        {
            binder << getValueOfAdmin();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Users::toJson() const
{
    Json::Value ret;
    if(getUserId())
    {
        ret["user_id"]=getValueOfUserId();
    }
    else
    {
        ret["user_id"]=Json::Value();
    }
    if(getUserName())
    {
        ret["user_name"]=getValueOfUserName();
    }
    else
    {
        ret["user_name"]=Json::Value();
    }
    if(getPassword())
    {
        ret["password"]=getValueOfPassword();
    }
    else
    {
        ret["password"]=Json::Value();
    }
    if(getOrgName())
    {
        ret["org_name"]=getValueOfOrgName();
    }
    else
    {
        ret["org_name"]=Json::Value();
    }
    if(getSignature())
    {
        ret["signature"]=getValueOfSignature();
    }
    else
    {
        ret["signature"]=Json::Value();
    }
    if(getAvatarId())
    {
        ret["avatar_id"]=getValueOfAvatarId();
    }
    else
    {
        ret["avatar_id"]=Json::Value();
    }
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getSalt())
    {
        ret["salt"]=getValueOfSalt();
    }
    else
    {
        ret["salt"]=Json::Value();
    }
    if(getAdmin())
    {
        ret["admin"]=getValueOfAdmin();
    }
    else
    {
        ret["admin"]=Json::Value();
    }
    return ret;
}
