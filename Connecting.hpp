#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "Database.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
using tcp = boost::asio::ip::tcp;

class Connecting : public std::enable_shared_from_this<Connecting> {
public:
    Connecting(tcp::socket socket);
    void start();

private:
    tcp::socket socket_;
    beast::flat_buffer buffer_{ 4096 };
    http::request<http::string_body> request_;
    http::response<http::dynamic_body> response_;

    void readRequest();
    void processRequest();
    void writeResponse();

    void createPostResponce();
    void createGetResponse();
};