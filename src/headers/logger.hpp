#ifndef LIGHTBALANCER_LOGGER_HPP
#define LIGHTBALANCER_LOGGER_HPP
#pragma once

struct LOGGER_INFO;
#define LOGGER_INFO_PTR LOGGER_INFO*

class Logger {
    public:
        Logger(LOGGER_INFO_PTR logger_info);
        ~Logger();
        void log(std::string message);
        void error(std::string error);
    private:
        LOGGER_INFO_PTR logger_info;
};

#endif