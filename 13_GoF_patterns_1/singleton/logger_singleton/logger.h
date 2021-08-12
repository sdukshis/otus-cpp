#pragma once

#include <fstream>
#include <string_view>

class FileLogger {
  public:
    static FileLogger &getLogger() {
        static FileLogger logger;
        return logger;
    }

    FileLogger(const FileLogger &other) = delete;

    FileLogger &operator=(const FileLogger &other) = delete;

    FileLogger(FileLogger &&other) = delete;

    FileLogger &operator=(FileLogger &&other) = delete;

    void info(const std::string_view &message) {
        logfile_ << "INFO:" << message << std::endl;
    }

    void warning(const std::string_view &message) {
        logfile_ << "WARN:" << message << std::endl;
    }

  private:
    FileLogger() : logfile_{logfilename, std::ios::out | std::ios::ate} {}
    ~FileLogger() = default;

    static constexpr std::string_view logfilename = "app.log";
    std::ofstream logfile_;
};

using Logger = FileLogger;
