#!/bin/bash

directoryx="$(dirname -- $(readlink -fn -- "$0"; echo x))"
BASEDIR="${directoryx%x}"
STARTDIR=$PWD

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

create_dirs() {
    mkdir /etc/lightbalancer
    mkdir /var/log/lightbalancer
}

create_resource_files() {
    cd $BASEDIR
    cp  ../samples/default.json /etc/lightbalancer/config.json
    touch /var/log/lightbalancer/info.log
    touch /var/log/lightbalancer/error.log
}

# As we support more flavors of Linux, we will add more package managers
# to this list.
debian_install() {
    root_checker()
    echo "[*] Installing dependencies for Debian-based Linux"
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

main() {
    linux_check
    dependency_install
    create_dirs
    create_resource_files
    echo "[!] Setup development environment for LightBalancer"
    exit 0
}

main