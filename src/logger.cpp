#include "logger.hpp"
#include <ctime>
#include <iostream>

std::string now_timestamp() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return std::string(buf);
}

Logger::Logger(LOGGER_INFO_PTR logger_info) {
    this->logger_info = logger_info;
}

Logger::~Logger() { }

void Logger::log(std::string message) {
    std::string timestamp = now_timestamp();
    message = "[" + timestamp + "] " + message;
    if (this->logger_info->logging) {
        FILE *log_file = fopen(this->logger_info->log_file.c_str(), "a");
        fprintf(log_file, "%s\n", message.c_str());
        fclose(log_file);
    }
    if (this->logger_info->stdoutput) {
        std::cout << message << std::endl;
    }
}

void Logger::error(std::string error) {
    std::string timestamp = now_timestamp();
    error = "[" + timestamp + "]" + error;
    if (this->logger_info->logging) {
        FILE *error_file = fopen(this->logger_info->error_file.c_str(), "a");
        fprintf(error_file, "%s\n", error.c_str());
        fclose(error_file);
    }
    if (this->logger_info->stdoutput) {
        std::cerr << "[" << timestamp << "] \033[1;33m" << error << "\033[0m" << std::endl;
    }
}