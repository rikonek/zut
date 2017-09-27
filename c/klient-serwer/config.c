#include <stdlib.h>
#include <libconfig.h>

#include "config.h"

void readConfig(appconfig *appcfg, const char *cfg_file)
{
    config_t cfg;
    config_init(&cfg);
    int port;

    if(!cfg_file)
    {
        cfg_file="server.cfg";
    }
    
    if(!config_read_file(&cfg, cfg_file))
    {
        config_destroy(&cfg);
        perror("Config file read error");
        exit(1);
    }

    if(!config_lookup_int(&cfg, "port", &port))
    {
        port=7777;
    }

    // convert int port to char ptr_port
    appcfg->ptr_port=malloc(6*sizeof(char));
    sprintf(appcfg->ptr_port,"%d",port);

    if(!config_lookup_int(&cfg, "max_connections", &appcfg->max_connections))
    {
        appcfg->max_connections=5;
    }

    config_destroy(&cfg);
}