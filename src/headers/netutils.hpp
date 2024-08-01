#ifndef LIGHTBALANCER_NETUTILS_HPP
#define LIGHTBALANCER_NETUTILS_HPP
#pragma once
#include <string>

//Check if the given string is an IP address
bool is_ipv4(std::string ip);

//Standard nslookup command uses the systems nameserverr to resolve the domain name
std::string nslookup(std::string domain_name);

#endif