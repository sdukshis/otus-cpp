// Внедрение зависимости (Dependency Injection)

#include <exception>
#include <iostream>
#include <string>

class IStorage {
  public:
    virtual void execute_query() = 0;
};

class TestStorage : public IStorage {
  public:
    void execute_query() override {
        std::cout << "... fetching data" << std::endl;
    }
};

class ReportFirst {
    TestStorage *storage;

  public:
    ReportFirst() {}

    void print() {
        storage->execute_query();
        std::cout << "done" << std::endl;
    }
};

class Report {
    IStorage *storage;

  public:
    Report(IStorage *storage_) : storage(storage_) {}

    void print() {
        storage->execute_query();
        std::cout << "done" << std::endl;
    }
};

int main() {
    Report report(new TestStorage);
    report.print();

    return 0;
}
