#include "Database.hpp"
#include <sstream>


json::array tokenize(std::string const& str, const char delim)
{
    std::stringstream ss(str);
    json::array out;

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(json::string(s));
    }
    return out;
}

Database::~Database() {
    destruct();
}

void Database::insertQuery(const std::string& query) {
    init();
    PQsendQuery(m_connection.get(), query.c_str());
}

json::array Database::selectQuery(const std::string& query) {
    init();
    PQsendQuery(m_connection.get(), query.c_str());
    auto res = PQgetResult(m_connection.get());
    int turple = PQntuples(res);
    int results = PQnfields(res);

    json::array resObj;
    for (int i = 0; i < turple; ++i) {
        json::object obj;
        for (int j = 0; j < results; ++j) {
            std::string name = PQfname(res, j);
            auto type = PQftype(res, j);
            switch (type)
            {
            case 600:
            case 1015: {
                std::string str = PQgetvalue(res, i, j);
                json::array elem = tokenize(str.substr(1, str.size() - 2), ',');
                obj[name] = elem;
                break;
            }
            default:
                auto elem = PQgetvalue(res, i, j);
                obj[name] = elem;
                break;
            }
        }
        resObj.push_back(obj);
    }
    return resObj;
}

void Database::init() {
    m_connection.reset(PQsetdbLogin(m_dbhost.c_str(), std::to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish);
}

void Database::destruct() {
    m_connection.reset();
}
