/**
 *
 *  db_test.cc
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 * 
 *  Drogon database test program
 * 
 */
#include "Users.h"
#include <drogon/orm/DbClient.h>
#include <trantor/utils/Logger.h>
#include <iostream>
#include <unistd.h>
using namespace drogon::orm;
#define RESET "\033[0m"
#define RED "\033[31m"   /* Red */
#define GREEN "\033[32m" /* Green */

void testOutput(bool isGood, const std::string &testMessage)
{
    if (isGood)
    {
        std::cout << GREEN << testMessage << "\t\tOK\n";
        std::cout << RESET;
    }
    else
    {
        std::cout << RED << testMessage << "\t\tBAD\n";
        std::cout << RESET;
        exit(-1);
    }
}

int main()
{
    trantor::Logger::setLogLevel(trantor::Logger::DEBUG);
    auto clientPtr = DbClient::newPgClient("host=127.0.0.1 port=5432 dbname=postgres user=antao", 1);
    LOG_DEBUG << "start!";
    sleep(1);
    //Prepare the test environment
    *clientPtr << "DROP TABLE IF EXISTS USERS" >>
        [](const Result &r) {
            testOutput(true, "Prepare the test environment(0)");
        } >>
        [](const DrogonDbException &e) {
            std::cerr << e.base().what() << std::endl;
            testOutput(false, "Prepare the test environment(0)");
        };
    *clientPtr << "CREATE TABLE users \
        (\
            user_id character varying(32),\
            user_name character varying(64),\
            password character varying(64),\
            org_name character varying(20),\
            signature character varying(50),\
            avatar_id character varying(32),\
            id serial PRIMARY KEY,\
            salt character varying(20),\
            admin boolean DEFAULT false,\
            CONSTRAINT user_id_org UNIQUE(user_id, org_name)\
        )" >>
        [](const Result &r) {
            testOutput(true, "Prepare the test environment(1)");
        } >>
        [](const DrogonDbException &e) {
            std::cerr << e.base().what() << std::endl;
            testOutput(false, "Prepare the test environment(1)");
        };
    /// Test1:DbClient streaming-type interface
    /// 1.1 insert,non-blocking
    *clientPtr << "insert into users \
        (user_id,user_name,password,org_name) \
        values($1,$2,$3,$4) returning *"
               << "pg"
               << "postgresql"
               << "123"
               << "default" >>
        [](const Result &r) {
            std::cout << "id=" << r[0]["id"].as<int64_t>() << std::endl;
            testOutput(r[0]["id"].as<int64_t>() == 1, "Prepare the test environment(1)");
        } >>
        [](const DrogonDbException &e) {
            std::cerr << e.base().what() << std::endl;
            testOutput(false, "Prepare the test environment(1)");
        };
    ///1.2 insert,blocking
    *clientPtr << "insert into users \
        (user_id,user_name,password,org_name) \
        values($1,$2,$3,$4) returning *"
               << "pg1"
               << "postgresql1"
               << "123"
               << "default"
               << Mode::Blocking >>
        [](const Result &r) {
            std::cout << "id=" << r[0]["id"].as<int64_t>() << std::endl;
            testOutput(r[0]["id"].as<int64_t>() == 2, "Prepare the test environment(1)");
        } >>
        [](const DrogonDbException &e) {
            std::cerr << e.base().what() << std::endl;
            testOutput(false, "Prepare the test environment(1)");
        };
    /// Add more testing here

    /// 2 DbClient execSqlAsync()...
    ///
    /// Model and Mapper....
    getchar();
}