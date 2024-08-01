#!/bin/bash

#Most distrobutions of Linux require root/sudo privs to install packages
root_checker() {
    if [[ $EUID != 0 ]]; then
        echo "[!] Error, this script must be run as root/sudo"
        exit 1
    fi
}

linux_check() {
    #Ensure not MacOS
    if [[ $(uname) == "Darwin" ]]; then
        echo "[!] Error, this tool is not supported on MacOS"
        exit 1
    fi
}

linux_check

# As we support more flavors of Linux, we will add more package managers
# to this list.
debian_install() {
    root_checker()
    apt update
    apt install -y gcc g++ make cmake openssl python3-dev libssl-dev libffi-dev zlib1g pkg-config
    echo "[*] Dependencies installed for Ubuntu!"
}

dependecy_install() {
    ## FIRST DEBIAN CHECK (Debian, Kali, Ubuntu, etc)
    if [[ -f /etc/debian_version ]]; then
        ubuntu_install
    else
        echo "[!] Error, this tool is not supported on this Linux distribution"
        exit 1
    fi
}