#include <iostream>
#include <memory>

#include "HTTPServer.h"

class HelloHandler : public HTTPRequestHandler {
  public:
    void handle_request(HTTPRequest &, HTTPResponse &response) override {
        response.status_code = 200;
        response.status_message = "OK";
        response.body = "<html><body><h1>Hello, world</h1></body></html>";
    }
};

class HelloHandlerFactory : public HTTPRequestHandlerFactory {
  public:
    std::unique_ptr<HTTPRequestHandler>
    create_request_handler(const HTTPRequest &request) override {
        if (request.method != "GET" or request.path != "/") {
            return nullptr;
        }
        return std::make_unique<HelloHandler>();
    }
};

int main() {
    HTTPServer server{std::make_unique<HelloHandlerFactory>()};

    HTTPRequest request;
    request.method = "GET";
    request.path = "/";
    std::cout << server.handle_request(request);
}