#include "server.hpp"
#include "logger.hpp"
#include "config.hpp"

LightBalancerServer::LightBalancerServer(CONFIG_PTR config) {
    this->config = config;
    this->logger = new Logger(config->logger_info);
}

LightBalancerServer::~LightBalancerServer() {
    delete this->logger;
}