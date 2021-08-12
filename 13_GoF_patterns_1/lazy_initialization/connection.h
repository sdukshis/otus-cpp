#pragma once

#include <string_view>

#include <asio.hpp>

class Connection {
public:
    Connection(const std::string_view &hostname)
        : sock_{io_ctx_} {
        asio::ip::tcp::resolver resolver(io_ctx_);
        asio::connect(sock_, resolver.resolve(hostname, "http"));            
    }


    void write(const char *data, size_t length) {
        asio::write(sock_, asio::buffer(data, length));
    }

    size_t read(char *data, size_t max_length) {
        return sock_.read_some(asio::buffer(data, max_length));
    }    

private:
    asio::io_context io_ctx_;
    asio::ip::tcp::socket sock_;
};
