// Ленивая инициализация (Lazy initialization)

#include <iostream>
#include <string>

class File {
    std::string name;

  public:
    File(const std::string &name_) : name(name_) {
        std::cout << "create " << name << std::endl;
    }
    ~File() { std::cout << "close " << name << std::endl; }
    void write(const std::string &line_) {
        std::cout << "write " << line_ << " into " << name << std::endl;
    }
};

void testFile(std::size_t dataCount, const std::string dataToWrite,
              const std::string &filename) {

    File file(filename);

    for (std::size_t i = 0; i < dataCount; ++i)
        file.write(dataToWrite);
}

class FileOnDemand {
    std::string name;
    File *file;

  public:
    FileOnDemand(const std::string &name_) : name(name_), file(nullptr) {}

    ~FileOnDemand() { delete file; }

    File *operator->() {
        if (!file) {
            file = new File(name);
        }
        return file;
    }
};

void testOnDemand(std::size_t dataCount, const std::string dataToWrite,
                  const std::string &filename) {
    FileOnDemand file(filename);

    for (std::size_t i = 0; i < dataCount; ++i)
        file->write(dataToWrite);
}

int main() {
    testFile(0, "hello world", "filename");

    testOnDemand(0, "hello world", "filename2");

    return 0;
}
