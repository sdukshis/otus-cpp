#pragma once

#include <memory>

#include "HTTPRequestHandler.h"

class HTTPRequestHandlerFactory {
  public:
    HTTPRequestHandlerFactory() = default;

    virtual ~HTTPRequestHandlerFactory() = default;

    virtual std::unique_ptr<HTTPRequestHandler>
    create_request_handler(const HTTPRequest &request) = 0;
};
