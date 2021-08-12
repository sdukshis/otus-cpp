#include <iostream>
#include <array>

#include "connection_wrapper.h"

const std::string_view request = 
"GET / HTTP/1.1\r\n"
"Host: pm.filonovpv.name\r\n"
"Connection: close\r\n"
"\r\n";

int main() {
    std::array<char, 1024> response;

    ConnectionWrapper connection("pm.filonovpv.name");
    connection->write(request.data(), request.size());
    size_t bytes_read = connection->read(response.data(), response.size());
    std::cout.write(response.data(), bytes_read);
}