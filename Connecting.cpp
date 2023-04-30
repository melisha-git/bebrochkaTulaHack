#include "Connecting.hpp"

Connecting::Connecting(tcp::socket socket) : socket_(std::move(socket)) {}

void Connecting::start() {
    readRequest();
}

void Connecting::readRequest() {
    auto self = shared_from_this();

    http::async_read(socket_, buffer_, request_, [self](beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);
        if (!ec)
            self->processRequest();
        });
}

void Connecting::processRequest() {
    response_.version(request_.version());
    response_.keep_alive(false);
    switch (request_.method())
    {
    case http::verb::get:
        response_.result(http::status::ok);
        response_.set(http::field::server, "BebrochkaTeam");
        createGetResponse();
        break;
    case http::verb::post:
        response_.result(http::status::ok);
        response_.set(http::field::server, "BebrochkaTeam");
        createPostResponce();
        break;
    }
    response_.set(http::field::access_control_allow_origin, "*");
    response_.set(http::field::access_control_allow_headers, "content-type");
    writeResponse();
}

void Connecting::createPostResponce() {
    Database db;
    if (request_.target() == "/register") {
        json::value value = json::parse(request_.body());
        if (value.is_object()) {
            json::object obj = value.as_object();
            if (!obj.at("name").is_string()) {
                return;
            }
            std::string name = obj.at("name").as_string().c_str();
            json::array selObj = db.selectQuery("SELECT id FROM users where name = \'" + name + "\';");
            if (selObj.size() == 0) {
                db.insertQuery("insert into users (name) values (\'" + name + "\');");
            }
        }
    }
}

void Connecting::createGetResponse() {
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
}

void Connecting::writeResponse() {
    auto self = shared_from_this();

    response_.content_length(response_.body().size());

    http::async_write(socket_, response_, [self](beast::error_code ec, std::size_t) {
        self->socket_.close();
    });
}
