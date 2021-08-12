#pragma once

#include <optional>
#include <string>
#include <string_view>
#include "connection.h"

class ConnectionWrapper {
public:
    ConnectionWrapper(const std::string_view &hostname)
        : hostname_{hostname}
        , conn_{std::nullopt}
    {}

    Connection& operator*() {
        ensure_connection();
        return conn_.operator*();
    }

    Connection* operator->() {
        ensure_connection();
        return conn_.operator->();
    }

private:

    void ensure_connection() {
        if (conn_.has_value()) {
            return;
        }
        conn_.emplace(hostname_);
    }

    std::string hostname_;
    std::optional<Connection> conn_;
};
