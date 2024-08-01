#ifndef LIGHTBALANCER_SERVER_HPP
#define LIGHTBALANCER_SERVER_HPP
#pragma once

class Logger;
struct CONFIG;
#define CONFIG_PTR CONFIG*

class LightBalancerServer {
    public:
        LightBalancerServer(CONFIG_PTR config);
        ~LightBalancerServer();
        void start();
        void stop();
    private:
        Logger* logger;
        CONFIG_PTR config;
};

#endif