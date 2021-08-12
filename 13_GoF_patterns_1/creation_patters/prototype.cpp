// Прототип (Prototype)

#include <iostream>
#include <map>

struct Base {};

struct Derived1 : Base {};

struct Derived2 : Base {};

void func(Base *object) {
    // auto clone = object;
}

class Connection {
  public:
    virtual void connection() = 0;

    virtual Connection *clone() = 0;
};

class TcpConnector : public Connection {
  public:
    void connection() override { std::cout << "tcp connection" << std::endl; }

  public:
    TcpConnector *clone() override { return new TcpConnector{}; }
};

class UdpConnector : public Connection {
  public:
    void connection() override { std::cout << "udp connection" << std::endl; }

  public:
    UdpConnector *clone() override { return new UdpConnector{}; }
};

int main() {
    Connection *tcpCon = new TcpConnector{};

    //

    std::cout << "primary" << std::endl;
    tcpCon->connection();

    auto mirror = tcpCon->clone();
    std::cout << "mirror" << std::endl;
    mirror->connection();

    return 0;
}
