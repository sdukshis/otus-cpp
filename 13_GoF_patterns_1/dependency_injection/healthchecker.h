#pragma once

#include "HTTPClient.h"
#include <stdexcept>
#include <iostream>

class Healthchecker {
  public:
    explicit Healthchecker(std::shared_ptr<HTTPClient> client)
        : client_{std::move(client)} {
        if (!client_) {
            throw std::invalid_argument{"client is null"};
        }
    }

    bool check(const std::string_view &host) {
        HTTPRequest request;
        request.method = "GET";
        request.path = "/";
        request.headers.emplace("Host", host);
        request.headers.emplace("Connection", "Close");

        try {
            client_->connect(host);
            HTTPResponse response = client_->request(request);
            return response.status_code / 100 == 2;
        } catch (...) {
            return false;
        }
    }

  private:
    std::shared_ptr<HTTPClient> client_;
};
