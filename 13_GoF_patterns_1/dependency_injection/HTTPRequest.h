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

inline void print_uri(std::ostream &stream, const HTTPRequest &request) {
    stream << request.path;
    if (!request.parameters.empty()) {
        auto it = request.parameters.cbegin();
        stream << '?' << it->first << '=' << it->second;
        for (++it; it != request.parameters.cend(); ++it) {
            stream << '&' << it->first << '=' << it->second;
        }
    }
}

inline std::ostream &operator<<(std::ostream &stream,
                                const HTTPRequest &request) {
    stream << request.method << ' ';
    print_uri(stream, request);
    stream << " HTTP/1.1\r\n";

    for (auto &[name, value] : request.headers) {
        stream << name << ": " << value << "\r\n";
    }
    stream << "\r\n";
    return stream;
}