#pragma once

#include <istream>
#include <map>
#include <ostream>
#include <string>

struct HTTPRequest {
    std::string method;
    std::string path;
    std::multimap<std::string, std::string> parameters;
    std::multimap<std::string, std::string> headers;
};

struct HTTPResponse {
    size_t status_code;
    std::string status_message;
    std::multimap<std::string, std::string> headers;
    std::string body;
};

class HTTPRequestHandler {
  public:
    HTTPRequestHandler() = default;

    virtual ~HTTPRequestHandler() = default;

    virtual void handle_request(HTTPRequest &request,
                                HTTPResponse &response) = 0;
};

inline std::ostream &operator<<(std::ostream &stream, const HTTPResponse &response) {
    stream << "HTTP1/1 " << response.status_code << ' '
           << response.status_message << "\r\n";
    for (auto &[name, value] : response.headers) {
        stream << name << ": " << value << "\r\n";
    }
    stream << "\r\n";
    stream << response.body;
    return stream;
}
