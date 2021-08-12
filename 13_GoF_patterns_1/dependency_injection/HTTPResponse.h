#pragma once

#include <string>
#include <map>
#include <ostream>

struct HTTPResponse {
    size_t status_code;
    std::string status_message;
    std::multimap<std::string, std::string> headers;
    std::string body;
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
