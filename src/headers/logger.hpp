#ifndef LIGHTBALANCER_LOGGER_HPP
#define LIGHTBALANCER_LOGGER_HPP
#pragma once
#include "config.hpp"

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