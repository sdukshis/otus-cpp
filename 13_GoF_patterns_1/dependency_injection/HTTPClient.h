#pragma once

#include <algorithm>
#include <asio.hpp>
#include <asio/streambuf.hpp>
#include <asio/write.hpp>
#include <string>
#include <string_view>

#include "HTTPRequest.h"
#include "HTTPResponse.h"

class HTTPClient {
  public:
    explicit HTTPClient() : sock_{io_ctx_} {}

    virtual ~HTTPClient() = default;

    virtual void connect(const std::string_view &host) {
        asio::ip::tcp::resolver resolver{io_ctx_};
        asio::connect(sock_, resolver.resolve(host, "http"));
    }

    virtual HTTPResponse request(const HTTPRequest &request) {
        asio::streambuf sb;
        std::ostream stream(&sb);
        stream << request;
        asio::write(sock_, sb);

        std::array<char, buffer_size_> read_buffer;
        size_t bytes_read = sock_.read_some(asio::buffer(read_buffer));

        return parse(read_buffer.data(), bytes_read);
    }

  protected:
    HTTPResponse parse(const char *data, size_t size) {
        // for simplicity copy all data inro reponse.body
        HTTPResponse response;
        response.status_code = 200;
        response.body = std::string{data, size};
        return response;
    }

  private:
    static constexpr size_t buffer_size_ = 1024;
    asio::io_context io_ctx_;
    asio::ip::tcp::socket sock_;
};