#ifndef LIGHTBALANCER_CONFIG_HPP
#define LIGHTBALANCER_CONFIG_HPP
#pragma once
#include <string>
#include <vector>

struct SERVER {
    int port;
    std::string interface;
};

struct ENDPOINT {
    std::string ip;
    int port;
};

struct SSL {
    int enabled;
    std::string certificate;
    std::string key;
};

struct LOGGER_INFO {
    int logging;
    std::string log_file;
    std::string error_file;
    int stdoutput; //Do we print to stdout as well
};

#define SERVER_PTR SERVER*
#define ENDPOINT_PTR ENDPOINT*
#define SSL_PTR SSL*
#define LOGGER_INFO_PTR LOGGER_INFO*

struct ENDPOINT_ARRAY {
    std::vector<ENDPOINT_PTR> endpoints;
    int size;
};


#define ENDPOINT_ARRRAY_PTR ENDPOINT_ARRAY*

struct CONFIG {
    SERVER_PTR server;
    ENDPOINT_ARRRAY_PTR endpoints;
    SSL_PTR ssl;
    LOGGER_INFO_PTR logger_info;
};

#define CONFIG_PTR CONFIG*

CONFIG_PTR load_config(std::string path);
void free_config(CONFIG_PTR config);

#endif