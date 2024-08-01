## LightBalancer Configuration Guide

This guide explains how to edit the configuration file for the lightbalancer tool. The configuration file uses JSON format.

The configuration file defaults to: /etc/lightbalance/config.json

### Server Settings

The `server` section configures the main server settings.

```json
"server": {
    "port": 80,
    "interface": "0.0.0.0"
}
```

- **`port`**: The port number on which the load balancer will listen (default: 80)
- **`interface`**: The network interface to bind to (default: "0.0.0.0" for all interfaces)

### Endpoints

The `endpoints` section is an array of backend servers to which the load balancer will distribute traffic.

```json
"endpoints": [
    {
        "ip": "192.168.10.12",
        "port": 8000
    },
    {
        "ip": "dnsname.com",
        "port": 8002
    }
]
```

Each endpoint has two properties:
- **`ip`**: The IP address or domain name of the backend server
- **`port`**: The port number on which the backend server is listening

You can add or remove endpoints as needed.

### SSL Configuration

The `ssl` section configures SSL/TLS settings.

```json
"ssl": {
    "enabled": false,
    "certificate": "",
    "key": ""
}
```

- **`enabled`**: Set to `true` to enable SSL/TLS, `false` to disable
- **`certificate`**: Path to the SSL certificate file (when SSL is enabled)
- **`key`**: Path to the SSL private key file (when SSL is enabled)

### Logging

The `logging` section configures the logging behavior.

```json
"logging": {
    "logging": true,
    "log_file": "/var/log/lightbalancer.log",
    "error_file": "/var/log/lightbalancer_error.log",
    "log_level": "info"
}
```

- **`logging`**: Set to `true` to enable logging, `false` to disable
- **`log_file`**: Path to the main log file
- **`error_file`**: Path to the error log file
- **`log_level`**: The logging level (e.g., "info", "debug", "warn", "error")

### Complete Configuration Example

```json
{
    "server": {
        "port": 80,
        "interface": "0.0.0.0"
    },
    "endpoints": [
        {
            "ip": "192.168.10.12",
            "port": 8000
        },
        {
            "ip": "dnsname.com",
            "port": 8002
        },
        {
            "ip": "dns2.ca",
            "port": 8000
        },
        {
            "ip": "comcast.net",
            "port": 8003
        }
    ],
    "ssl": {
        "enabled": false,
        "certificate": "",
        "key": ""
    },
    "logging": {
        "logging": true,
        "log_file": "/var/log/lightbalancer.log",
        "error_file": "/var/log/lightbalancer_error.log",
        "log_level": "info"
    }
}
```

Ensure that the JSON file is properly formatted and all required fields are filled out according to your specific requirements.