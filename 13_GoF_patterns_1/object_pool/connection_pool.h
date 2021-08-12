#pragma once

#include <string_view>
#include <vector>

#include <asio.hpp>

class ConnectionPool {
  public:
    class Connection {
      public:
        explicit Connection(asio::ip::tcp::socket &&sock, ConnectionPool *pool = nullptr)
            : sock_(std::move(sock)), pool_{pool} {}

        Connection(const Connection &other) = delete;

        Connection &operator=(const ConnectionPool &other) = delete;

        Connection(Connection &&other)
            : sock_{std::move(other.sock_)}, pool_{other.pool_} {
            other.pool_ = nullptr;
        }

        Connection &operator=(Connection &&other) {
            sock_ = std::move(other.sock_);
            pool_ = other.pool_;
            other.pool_ = nullptr;
            return *this;
        }

        ~Connection() {
            if (!pool_) {
                return;
            }
            try {
                pool_->recycle(*this);
            } catch (...) {
                // ignore possibel excptions
                // assume memory allocation error in ConnectionPool std::vector
            }
        }

        void write(const char *data, size_t length) {
            asio::write(sock_, asio::buffer(data, length));
        }

        size_t read(char *data, size_t max_length) {
            return sock_.read_some(asio::buffer(data, max_length));
        }

      private:
        asio::ip::tcp::socket sock_;
        ConnectionPool *pool_;
    };

    ConnectionPool(const std::string_view hostname, size_t size)
        : hostname_{hostname}, max_pool_size_{size} {}

    ConnectionPool(const ConnectionPool &other) = delete;

    ConnectionPool &operator=(ConnectionPool &other) = delete;

    ConnectionPool(ConnectionPool &&other) = delete;

    ConnectionPool &operator=(ConnectionPool &&other) = delete;

    Connection get_connection() {
        if (!conn_pool_.empty()) {
            Connection conn{std::move(conn_pool_.back())};
            conn_pool_.pop_back();
            return conn;
        }
        return new_connection();
    }

  private:
    Connection new_connection() {
        asio::ip::tcp::socket sock(io_ctx_);
        asio::ip::tcp::resolver resolver(io_ctx_);
        asio::connect(sock, resolver.resolve(hostname_, "http"));

        return Connection{std::move(sock), this};
    }

    void recycle(Connection &conn) {
        if (conn_pool_.size() < max_pool_size_) {
            conn_pool_.emplace_back(std::move(conn));
        }
    }

    const std::string hostname_;
    const size_t max_pool_size_;
    std::vector<Connection> conn_pool_;
    asio::io_context io_ctx_;
};
