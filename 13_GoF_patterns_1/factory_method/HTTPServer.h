#pragma once

#include <memory>

#include "HTTPRequestHandlerFactory.h"

class HTTPServer {
  public:
    HTTPServer(std::shared_ptr<HTTPRequestHandlerFactory> factory)
        : factory_{std::move(factory)} {}

    HTTPResponse handle_request(HTTPRequest &request) {
        HTTPResponse response;
        response.headers.emplace("Server", "C++/0.1");

        if (!factory_) {
            response.status_code = 501;
            response.status_message = "Not Implemented";
            return response;
        }
        auto handler = factory_->create_request_handler(request);
        if (!handler) {
            response.status_code = 405;
            response.status_message = "Method Not Allowed";
            return response;
        }
        handler->handle_request(request, response);

        // Fill Content-Length
        if (!response.body.empty() and
            (response.headers.find("Content-Length") ==
             response.headers.end())) {
            response.headers.emplace("Content-Length",
                                     std::to_string(response.body.size()));
        }
        return response;
    }

  private:
    std::shared_ptr<HTTPRequestHandlerFactory> factory_;
};
