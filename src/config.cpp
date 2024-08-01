#include "config.hpp"
#include "netutils.hpp"
#include "nlohmann/json.hpp"
#include <stdio.h>
#include <fstream>

using json = nlohmann::json;

/* MALLOC STRUCT POINTERS */
//Malloc a new SERVER struct pointer
SERVER_PTR malloc_server() {
    SERVER_PTR server = (SERVER *)malloc(sizeof(SERVER));
    return server;
}

//Malloc a new ENDPOINT struct pointer
ENDPOINT_PTR malloc_endpoint() {
    ENDPOINT_PTR endpoint = (ENDPOINT *)malloc(sizeof(ENDPOINT));
    return endpoint;
}

//Malloc a new SSL struct pointer
SSL_PTR malloc_ssl() {
    SSL_PTR ssl = (SSL *)malloc(sizeof(SSL));
    return ssl;
}

//Malloc a new LOGGER_INFO struct pointer
LOGGER_INFO_PTR malloc_logger_info() {
    LOGGER_INFO_PTR logger_info = (LOGGER_INFO *)malloc(sizeof(LOGGER_INFO));
    return logger_info;
}

//Malloc a new ENDPOINT_ARRAY struct pointer
ENDPOINT_ARRAY_PTR malloc_endpoint_array() {
    ENDPOINT_ARRAY_PTR endpoint_array = (ENDPOINT_ARRAY *)malloc(sizeof(ENDPOINT_ARRAY));
    return endpoint_array;
}

//Malloc a new CONFIG struct pointer
CONFIG_PTR malloc_config() {
    CONFIG_PTR config = (CONFIG *)malloc(sizeof(CONFIG));
    return config;
}

/* FREE STRRUCT POINTERS */
//Free a SERVER struct pointer  
void free_server(SERVER_PTR server) {
    free(server);
}

//Free a ENDPOINT struct pointer
void free_endpoint(ENDPOINT_PTR endpoint) {
    free(endpoint);
}

//Free a SSL struct pointer
void free_ssl(SSL_PTR ssl) {
    free(ssl);
}

//Free a LOGGER_INFO struct pointer
void free_logger_info(LOGGER_INFO_PTR logger_info) {
    free(logger_info);
}

//Free a ENDPOINT_ARRAY struct pointer
void free_endpoint_array(ENDPOINT_ARRAY_PTR endpoint_array) {
    //Free the innerr ENDPOINT_PTR
    for (int i = 0; i < endpoint_array->size; i++) {
        free_endpoint(endpoint_array->endpoints[i]);
    }
    free(endpoint_array);
}

//Free a CONFIG struct pointer
void free_config(CONFIG_PTR config) {
    free_server(config->server);
    free_ssl(config->ssl);
    free_logger_info(config->logger_info);
    free_endpoint_array(config->endpoints);
    free(config);
}

SERVER_PTR load_server(json server) {
    SERVER_PTR server_ptr = malloc_server();
    server_ptr->port = server["port"];
    server_ptr->interface = server["interface"];
    return server_ptr;
}

SSL_PTR load_ssl(json ssl) {
    SSL_PTR ssl_ptr = malloc_ssl();
    ssl_ptr->enabled = ssl["enabled"];
    ssl_ptr->certificate = ssl["certificate"];
    ssl_ptr->key = ssl["key"];
    return ssl_ptr;
}

LOGGER_INFO_PTR load_logger_info(json logger_info) {
    LOGGER_INFO_PTR logger_info_ptr = malloc_logger_info();
    logger_info_ptr->logging = logger_info["logging"];
    logger_info_ptr->log_file = logger_info["log_file"];
    logger_info_ptr->error_file = logger_info["error_file"];
    logger_info_ptr->log_level = logger_info["log_level"];
    return logger_info_ptr;
}

ENDPOINT_ARRAY_PTR load_endpoints(json endpoints) {
    ENDPOINT_ARRAY_PTR endpoint_array = malloc_endpoint_array();
    int size = 0;
    for (json::iterator it = endpoints.begin(); it != endpoints.end(); ++it) {
        ENDPOINT_PTR endpoint = malloc_endpoint();
        std::string ip = it.value()["ip"];
        if (is_ipv4(ip)) {
            endpoint->ip = ip;
        } else {
            endpoint->ip = nslookup(ip);
        }
        endpoint->port = it.value()["port"];
        endpoint_array->endpoints.push_back(endpoint);
        size += 1;
    }
    endpoint_array->size = size;
    return endpoint_array;
}

CONFIG_PTR load_config(std::string path) {
    CONFIG_PTR config = malloc_config();
    json j;
    std::ifstream file(path);
    if (!file.is_open()) {
        return NULL;
    }
    file >> j;
    file.close();
    config->server = load_server(j["server"]);
    config->endpoints = load_endpoints(j["endpoints"]);
    config->ssl = load_ssl(j["ssl"]);
    config->logger_info = load_logger_info(j["logger_info"]);
    return config;
}