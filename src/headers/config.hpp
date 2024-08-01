#ifndef LIGHTBALANCER_CONFIG_HPP
#define LIGHTBALANCER_CONFIG_HPP
#pragma once
#include <string>
#include <vector>

//Server information
struct SERVER {
    int port;
    std::string interface;
};

//Endpoint information
struct ENDPOINT {
    std::string ip;
    int port;
};

//SSL information
struct SSL {
    int enabled;
    std::string certificate;
    std::string key;
};

//Logger information
struct LOGGER_INFO {
    int logging;
    std::string log_file;
    std::string error_file;
    std::string log_level;
};

#define SERVER_PTR SERVER*
#define ENDPOINT_PTR ENDPOINT*
#define SSL_PTR SSL*
#define LOGGER_INFO_PTR LOGGER_INFO*

//Endpoint array
struct ENDPOINT_ARRAY {
    std::vector<ENDPOINT_PTR> endpoints;
    int size;
};


#define ENDPOINT_ARRAY_PTR ENDPOINT_ARRAY*

//Configuration information
struct CONFIG {
    SERVER_PTR server;
    ENDPOINT_ARRAY_PTR endpoints;
    SSL_PTR ssl;
    LOGGER_INFO_PTR logger_info;
};

#define CONFIG_PTR CONFIG*

//Load a configuration file to a pointer
CONFIG_PTR load_config(std::string path);
//Free a configuration pointer
void free_config(CONFIG_PTR config);

#endif