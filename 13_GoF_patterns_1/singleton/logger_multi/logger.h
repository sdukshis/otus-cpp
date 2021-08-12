#pragma once

#include <fstream>
#include <string_view>

class FileLogger {
  public:
    FileLogger()
        : logfile_{logfilename, std::ios_base::out | std::ios_base::ate} {}

    FileLogger(const FileLogger &other) = delete;

    FileLogger &operator=(const FileLogger &other) = delete;

    ~FileLogger() = default;

    FileLogger(FileLogger &&other) = default;

    FileLogger &operator=(FileLogger &&other) = default;

    void info(const std::string_view &message) {
        logfile_ << "INFO:" << message << std::endl;
    }

    void warning(const std::string_view &message) {
        logfile_ << "WARN:" << message << std::endl;
    }

  private:
    static constexpr std::string_view logfilename = "app.log";
    std::ofstream logfile_;
};

using Logger = FileLogger;
