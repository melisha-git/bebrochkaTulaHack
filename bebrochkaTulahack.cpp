#include <iostream>
#include <string>
#include <boost/beast.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;
ip::tcp::endpoint endpnt{ ip::address::from_string("192.168.31.102"), 8080 };
io_context context;

ip::tcp::acceptor acceptor{ context, endpnt };

std::string getResponce() {
    std::string content = "\'{\"name\":\"Иван\",\n\"age\":37,\n\"mother\":\n{\"name\":\"Ольга\",\n\"age\":58},\n\"children\":\n[\"Маша\",\n\"Игорь\",\n\"Таня\"],\n\"married\":\ntrue,\n\"dog\":\nnull}\'";
    std::string responce = "HTTP/1.0 200 OK\r\nContent - length: " + std::to_string(content.size()) + "Connection: close\r\nContent - Type: application/json\r\n\r\n" + content;
    return responce;
}

void reader_writer(const std::shared_ptr<ip::tcp::socket> &socket, 
    std::shared_ptr<std::vector<char>> buffer = std::make_shared<std::vector<char>>(4096)) {

    socket->async_read_some(boost::asio::buffer(*buffer), [socket, buffer](auto error, auto n) {
        std::cout << "read " << n << ' ' << error << std::endl;
        if (error) {
            socket->close();
            return;
        }
        buffer->clear();
        std::string responce = getResponce();
        std::shared_ptr<std::vector<char>> res = std::make_shared<std::vector<char>>(responce.begin(), responce.end());
        socket->async_write_some(boost::asio::buffer(res->data(), res->size()), [socket, buffer](auto error, auto n) {
            std::cout << "write " << n << ' ' << error << std::endl;
            socket->close();
            return;
        });
    });
}

void accept() {
    std::shared_ptr<ip::tcp::socket> socket = std::make_shared<ip::tcp::socket>(context);

    acceptor.async_accept(*socket, [socket](const auto& error) {
        std::cout << "accept " << error << std::endl;
        if (error)
            return;
        reader_writer(socket);
        accept();
    });
}

int main()
{
    accept();
    context.run();
    return 0;
}
