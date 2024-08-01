#include "config.hpp"
#include "netutils.hpp"
#include "nlohmann/json.hpp"
#include <stdio.h>

using json = nlohmann::json;

ENDPOINT_ARRRAY_PTR load_endpoints(json endpoints) {
    ENDPOINT_ARRRAY_PTR endpoint_array = (ENDPOINT_ARRAY *)malloc(sizeof(ENDPOINT_ARRAY));
    int size = 0;
    for (json::iterator it = endpoints.begin(); it != endpoints.end(); ++it) {
        ENDPOINT_PTR endpoint = (ENDPOINT *)malloc(sizeof(ENDPOINT));
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

void free_endpoint_array(ENDPOINT_ARRRAY_PTR endpoint_array) {
    for (int i = 0; i < endpoint_array->size; i++) {
        free(endpoint_array->endpoints[i]);
    }
    free(endpoint_array);
}

CONFIG_PTR load_config(std::string path) {
    CONFIG_PTR config = (CONFIG *)malloc(sizeof(CONFIG));

    return config;
}