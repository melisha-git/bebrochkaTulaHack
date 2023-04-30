#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <iostream>
#include "Connecting.hpp"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

void accepcing(tcp::acceptor& acceptor, tcp::socket& socket) {
    acceptor.async_accept(socket, [&](beast::error_code ec) {
        if (!ec)
            std::make_shared<Connecting>(std::move(socket))->start();
        accepcing(acceptor, socket);
    });
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