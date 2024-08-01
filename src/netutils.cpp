#include "netutils.hpp"
#include <arpa/inet.h>
#include <netdb.h>

bool is_ipv4(std::string ip) {
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
    return result != 0;
}

std::string nslookup(std::string domain_name) {
    struct hostent *he;
    he = gethostbyname(domain_name.c_str());
    if (he == NULL) {
        return "";
    }
    char *ip = inet_ntoa(*((struct in_addr *)he->h_addr));
    return std::string(ip);
}