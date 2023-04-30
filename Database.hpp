#pragma once

#include <string>
#include <boost/json.hpp>
#include <libpq-fe.h>

namespace json = boost::json;

class Database {
public:
    Database() = default;

    ~Database();

    void insertQuery(const std::string& query);

    json::array selectQuery(const std::string& query);

private:
    std::string m_dbhost = "45.12.238.30";
    int         m_dbport = 5431;
    std::string m_dbname = "postgres";
    std::string m_dbuser = "your_user";
    std::string m_dbpass = "your_password";

    std::shared_ptr<PGconn>  m_connection;

    void init();

    void destruct();
};