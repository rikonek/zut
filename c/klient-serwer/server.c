#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h> // socket
// #include <netinet/in.h> // sockaddr_in
#include <string.h> // memset, strcspn
// #include <ctime>
// #include <unistd.h> // usleep
// #include <arpa/inet.h> // inet_ntoa
#include <sys/wait.h>
#include <signal.h> // sigaction
#include <netdb.h> // addrinfo


#include "config.h"

void sigchld_handler(int s);

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sigaction sa;
    struct addrinfo hints, *result;

    appconfig *appcfg=malloc(sizeof(appconfig));
    readConfig(appcfg, argv[1]);

    printf("Server config:\n");
    printf(" - port: %d\n", appcfg->port);
    printf(" - max connections: %d\n", appcfg->max_connections);
    printf("Server starting...\n");

    sa.sa_handler=sigchld_handler; // collect dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=SA_RESTART;
    if(-1==sigaction(SIGCHLD, &sa, NULL))
    {
        perror("sigaction");
        exit(1);
    }

    // inetPassiveSocket(appcfg->port, SOCK_STREAM, NULL, TRUE, appcfg->max_connections);
    // inetPassiveSocket(const char *service, int type, socklen_t *addrlen, Boolean doListen, int backlog)

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags=AI_PASSIVE; // use all IP address
    hints.ai_family=AF_UNSPEC; // use IPv4 and IPv6
    hints.ai_socktype=SOCK_STREAM; // TCP


    int gai;
    gai=getaddrinfo(NULL, appcfg->ptr_port, &hints, &result);
    if(gai!=0)
    {
        perror("getaddrinfo");
        exit(1);
    }




    freeaddrinfo(result);
    free(appcfg);

    return 0;
}

void sigchld_handler(int s)
{
    while(wait(NULL)>0);
}