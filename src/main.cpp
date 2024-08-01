#include "server.hpp"
#include "config.hpp"
#include <string>

int main(int argc, char **argv) {
    std::string config_path = "/etc/lightbalancer/config.json";
    CONFIG_PTR config = load_config(config_path);
    if (config == NULL) {
        return 1;
    }
    LightBalancerServer server(config);
    server.start();
    free_config(config); //Free config on exit
    return 0;
}