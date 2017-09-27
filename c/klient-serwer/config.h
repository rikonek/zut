#ifndef CONFIG_H
#define CONFIG_H

typedef struct appconfig
{
    char *ptr_port; // getaddrinfo require char *
    int max_connections;
} appconfig;

void readConfig(appconfig *appcfg, const char *cfg_file);

#endif