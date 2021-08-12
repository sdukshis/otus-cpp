// Объектный пул (Object pool)

#include <array>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Connection {};

class ConnectionPool {
  private:
    using ConnectionPtr = std::unique_ptr<Connection>;
    struct ConnectionBlock {
        ConnectionPtr connection;
        bool busy;
    };

    std::vector<ConnectionBlock> m_pool;

  public:
    Connection *get() {
        for (size_t i = 0; i < m_pool.size(); ++i) {
            if (!m_pool[i].busy) {
                m_pool[i].busy = true;
                return m_pool[i].connection.get();
            }
        }
        if (m_pool.size() < max_elems) {
            //?????
            auto block = ConnectionBlock{ConnectionPtr{new Connection}, true};
            m_pool.emplace_back(std::move(block));

            return m_pool.back().connection.get();
        }
    }

    void put(Connection *object) {
        for (size_t i = 0; i < m_pool.size(); ++i) {
            if (m_pool[i].connection.get() == object) {
                m_pool[i].busy = false;
                break;
            }
        }
    }

    ~ConnectionPool() = default;
};

int main() {
    ConnectionPool pool;

    auto report_conn = pool.get();
    ///...
    pool.put(report_conn);

    auto admin_conn = pool.get();
    pool.put(admin_conn);

    return 0;
}
