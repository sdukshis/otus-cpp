// Одиночка (Singleton)
// Одиночка решает сразу две проблемы, нарушая принцип единственной
// ответственности класса: 1) Гарантирует наличие единственного экземпляра
// класса. Чаще всего это полезно для доступа к какому-то общему ресурсу,
// например, базе данных. 2) Предоставляет глобальную точку доступа.

#include <iostream>
#include <string>

class Logger {
  public:
    static Logger &Instance() {
        static Logger instance;
        return instance;
    }

    void info(const std::string &message) const {
        std::cout << "info: " << message << std::endl;
    }

    void warning(const std::string &message) const {
        std::cout << "warning: " << message << std::endl;
    }

  private:
    Logger() = default;

    Logger(const Logger &root) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger(Logger &&root) = delete;
    Logger &operator=(Logger &&) = delete;

    ~Logger() = default;
};

int main() {
    // Compile error
    // error: 'Logger::Logger()' is private within this context
    // Logger logger;

    Logger::Instance().info("info");
    Logger::Instance().warning("warning");

    Logger &logger = Logger::Instance();
    logger.info("info");
    logger.warning("warning");

    // Compile error
    // error: use of deleted function 'Logger::Logger(const Logger&)'
    // Logger logger2 = logger;

    // Compile error
    // error: 'Logger::~Logger()' is private within this context
    // (&logger)->~Logger();

    return 0;
}
