#pragma once

#include <string_view>

#include "HTTPRequest.h"

class HTTPRequestBuilder {
  public:
    HTTPRequestBuilder() = default;

    HTTPRequestBuilder &method(const std::string_view &method_) {
        request.method = method_;
        return *this;
    }

    HTTPRequestBuilder &path(const std::string_view &path_) {
        request.path = path_;
        return *this;
    }

    HTTPRequestBuilder &param(const std::string_view &name,
                              const std::string_view &value) {
        request.parameters.emplace(name, value);
        return *this;
    }

    HTTPRequestBuilder &header(const std::string_view &name,
                               const std::string_view &value) {
        request.headers.emplace(name, value);
        return *this;
    }

    HTTPRequest build() {
        HTTPRequest ret = std::move(request);
        request = HTTPRequest{};
        return ret;
    }

  private:
    HTTPRequest request;
};