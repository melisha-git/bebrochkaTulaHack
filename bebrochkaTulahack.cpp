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

namespace beast = boost::beast;
using namespace boost::json;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class http_connection : public std::enable_shared_from_this<http_connection> {
public:
    http_connection(tcp::socket socket) : socket_(std::move(socket)) {}

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

        response_.result(http::status::ok);
        response_.set(http::field::server, "Beast");
        create_response();

        write_response();
    }

    void create_response() {
        object obj;
        obj["pi"] = 3.141;
        obj["happy"] = true;
        obj["name"] = "Boost";
        response_.set(http::field::content_type, "application/json");
        beast::ostream(response_.body()) << obj;
    }

    void write_response() {
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        http::async_write(socket_, response_, [self](beast::error_code ec, std::size_t) {
                self->socket_.close();
        });
    }
};

void http_server(tcp::acceptor& acceptor, tcp::socket& socket) {
    acceptor.async_accept(socket, [&](beast::error_code ec) {
        if (!ec)
            std::make_shared<http_connection>(std::move(socket))->start();
        http_server(acceptor, socket);
    });
}

int main() {
    try
    {
        tcp::endpoint endpnt{ boost::asio::ip::address::from_string("192.168.31.102"), 8080 };

        net::io_context ioc{ 1 };
        tcp::acceptor acceptor{ ioc, endpnt };
        tcp::socket socket{ ioc };
        http_server(acceptor, socket);

        ioc.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}