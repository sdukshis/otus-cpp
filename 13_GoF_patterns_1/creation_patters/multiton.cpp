// Пул одиночек (Multiton)

#include <iostream>
#include <map>
#include <string>
#include <tuple>

enum class Tag { main, db };

class Logger {
    Tag t;

  public:
    static Logger &Instance(Tag t) {
        static std::map<Tag, Logger> instance;
        auto i = instance.find(t);
        if (i == instance.end()) {
            bool b;
            std::tie(i, b) = instance.emplace(std::make_pair(t, Logger{t}));
        }
        return i->second;
    }

    void info(const std::string &message) const {
        std::cerr << "info: [" << int(t) << "] " << message << std::endl;
    }

    void warn(const std::string &message) const {
        std::cerr << "warning: [" << int(t) << "] " << message << std::endl;
    }

  private:
    Logger() = default;

    Logger(Tag t_) : t(t_) {}

    // TODO
    //     Logger(const Logger&) = default;
    //     Logger(Logger&&) = default;
    //     Logger& operator=(const Logger&) = default;
    //     Logger& operator=(Logger&&) = default;
    //     ~Logger() = default;
};

int main() {
    Logger::Instance(Tag::main).info("started");
    Logger::Instance(Tag::db).warn("no db");
    Logger::Instance(Tag::main).info("finished");

    return 0;
}
