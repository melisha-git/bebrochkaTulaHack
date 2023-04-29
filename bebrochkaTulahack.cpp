#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <libpq-fe.h>
#include <fstream>

namespace beast = boost::beast;
namespace json = boost::json;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Database {
public:
    Database() {
        m_connection.reset(PQsetdbLogin(m_dbhost.c_str(), std::to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish);
    }

    ~Database() {
        m_connection.reset();
    }

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

    json::array selectQuery(const std::string& query) {
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
                if (type == 1015) {
                    std::string arr = PQgetvalue(res, i, j);
                    json::array elem = tokenize(arr.substr(1, arr.size() - 2), ',');
                    obj[name] = elem;
                }
                else {
                    auto elem = PQgetvalue(res, i, j);
                    obj[name] = elem;
                }
            }
            resObj.push_back(obj);
        }
        return resObj;
    }
private:
    std::string m_dbhost = "45.12.238.30";
    int         m_dbport = 5431;
    std::string m_dbname = "postgres";
    std::string m_dbuser = "your_user";
    std::string m_dbpass = "your_password";

    std::shared_ptr<PGconn>  m_connection;
};

class connecting : public std::enable_shared_from_this<connecting> {
public:
    connecting(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() {
        read_request();
    }

private:
    tcp::socket socket_;
    beast::flat_buffer buffer_{ 4096 };
    http::request<http::dynamic_body> request_;
    http::response<http::dynamic_body> response_;

    void read_request() {
        auto self = shared_from_this();

        http::async_read( socket_, buffer_, request_, [self](beast::error_code ec, std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);
                if (!ec)
                    self->process_request();
        });
    }

    void process_request() {
        response_.version(request_.version());
        response_.keep_alive(false);
        switch (request_.method())
        {
        case http::verb::get:
            response_.result(http::status::ok);
            response_.set(http::field::server, "BebrochkaTeam");
            create_response();
        }

        write_response();
    }

    void create_response() {
        Database db;
        json::array obj;
        if (request_.target() == "/api" || request_.target() == "/") {
            obj = db.selectQuery("SELECT * FROM dataHack;");
            response_.set(http::field::content_type, "application/json");
        }
        else if (request_.target().find("/places") != std::string::npos) {
            std::string target = request_.target();
            target = target.substr(7);
            if (target.empty() || target == "/") {
                obj = db.selectQuery("select * from places;");
                response_.set(http::field::content_type, "application/json");
            }
            else {
                if (target[0] == '/') {
                    target = target.substr(1);
                }
                bool isNum = std::all_of(target.begin(), target.end(), ::isdigit);
                if (isNum)
                    obj = db.selectQuery("select * from places where id = " + target + ";");
                else
                    obj = db.selectQuery("select * from places where \"type\" = \'" + target + "\';");
                response_.set(http::field::content_type, "application/json");
            }
        }
        else if (request_.target() == "/users") {
            obj = db.selectQuery("select * from users;");
            response_.set(http::field::content_type, "application/json");
        }
        else if (request_.target() == "/ML") {
            obj = db.selectQuery("SELECT id, user_id, place_id, evaluation, to_char(last_time, 'YYYYMMDD') FROM dataHack where user_id = 1;");
            response_.set(http::field::content_type, "application/json");
        }
        else
            response_.result(http::status::not_found);
        beast::ostream(response_.body()) << obj;
        response_.set(http::field::access_control_allow_origin, "*");
    }

    void write_response() {
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        http::async_write(socket_, response_, [self](beast::error_code ec, std::size_t) {
                self->socket_.close();
        });
    }
};

void accepcing(tcp::acceptor& acceptor, tcp::socket& socket) {
    acceptor.async_accept(socket, [&](beast::error_code ec) {
        if (!ec)
            std::make_shared<connecting>(std::move(socket))->start();
        accepcing(acceptor, socket);
    });
}

void create()
{
    // file pointer
    std::fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("reportcard.csv", std::ios::out | std::ios::app);

    std::cout << "Enter the details of 5 students:"
        << " roll name maths phy chem bio" << std::endl;

    int roll, phy, chem, math, bio;
    std::string name;

    // Read the input

        std::cin >> roll
            >> name
            >> math
            >> phy
            >> chem
            >> bio;

        // Insert the data to file
        fout << roll << ", "
            << name << ", "
            << math << ", "
            << phy << ", "
            << chem << ", "
            << bio
            << "\n";
}

int main() {

    try
    {
        tcp::endpoint endpnt{ boost::asio::ip::address::from_string("192.168.0.105"), 8080 };

        net::io_context context{ 1 };
        tcp::acceptor acceptor{ context, endpnt };
        tcp::socket socket{ context };
        accepcing(acceptor, socket);

        context.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}