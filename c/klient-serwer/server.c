#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

// #include <iostream>
// #include "cxxopts.hpp"

#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <string.h> // memset, strcspn
// #include <ctime>
// #include <unistd.h> // usleep
// #include <arpa/inet.h> // inet_ntoa
#include <sys/wait.h>
#include <signal.h> // sigaction

void sigchld_handler(int s);

int main(int argc, char *argv[])
{
    config_t cfg;
    int port, max_connections;
    config_init(&cfg);

    if(!config_read_file(&cfg, "server.cfg"))
    {
        config_destroy(&cfg);
        perror("Config file read error");
        exit(1);
    }

    if(!config_lookup_int(&cfg, "port", &port))
    {
        port=7777;
    }

    if(!config_lookup_int(&cfg, "max_connections", &max_connections))
    {
        max_connections=5;
    }

    printf("Server config:\n");
    printf("- port: %d\n", port);
    printf("- max connections: %d\n", max_connections);
    printf("Server starting...\n");


    int server_fd, new_fd;
    int yes=1;
    struct sockaddr_in address;
    struct sigaction sa;

    char buffer[1024]={0};
    char *msg_welcome = "Welcome client. Type 'exit' to quit.";
    // char *msg_ack="The message was delivered";

    server_fd=socket(AF_INET, SOCK_STREAM, 0); // create socket
	if(-1==server_fd)
	{
		perror("Socket create failed");
		exit(1);
    }

    /**
     * Fix to "Address already in use"
     * @return int, 0 on success, -1 on error
     */
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes, sizeof(yes)))
    {
        perror("Socket set option failed");
        exit(1);
    }

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY; // use my IP address
    address.sin_port=htons(port); // host to network short // 0 for random port
    memset(&(address.sin_zero),0,8); // sin_zero set to 0

    /**
     * Bind to port
     * @return int, 0 on success, -1 on error
     */
    if(bind(server_fd, (struct sockaddr *) &address, sizeof(address)))
    {
        perror("Binding stream socket");
        exit(1);
    }

    /**
     * @return int, 0 on success, -1 on error
     */
    if(listen(server_fd, max_connections))
    {
        perror("Listen");
        exit(1);
    }

    printf("server# Waiting for connections\n");

    sa.sa_handler=sigchld_handler; // collect dead processes
    sigemptyset( &sa.sa_mask );
    sa.sa_flags=SA_RESTART;
    if(-1==sigaction( SIGCHLD, &sa, NULL))
    {
        perror("sigaction");
        exit(1);
    }

    while(1) // accept loop
    {
        int addrlen=sizeof(address);
        if((new_fd=accept(server_fd, (struct sockaddr *) &address, (socklen_t*) &addrlen))<0)
        {
            perror("Accept");
            exit(1);
        }
        printf("client# Client connected from %i:%i\n", inet_ntoa( address.sin_addr ), address.sin_port);

    //     if(!fork())
    //     {
    //         // child process
    //         close(server_fd); // child doesn't need listener
    //         if(-1==send(new_fd, msg_welcome, strlen(msg_welcome), 0))
    //         {
    //             perror("Send");
    //             exit(1);
    //         }

    //         while(1)
    //         {
    //             memset(&buffer[0],0,sizeof(buffer)); // clear old buffer                
    //             if(-1==recv(new_fd, buffer, 1024, 0))
    //             {
    //                 perror("Recv");
    //                 exit(1);
    //             }
    //             buffer[strcspn(buffer,"\r\n")]=0; // remove new line

    //             int i=0;
    //             char *buffexp;
    //             buffexp=strtok(buffer,"#");
    //             while(buffexp!=NULL)
    //             {
    //                 i++;
    //                 if(strcmp(buffexp,"exit")==0)
    //                 {
    //                     cout << "client# Connection closed by client " << inet_ntoa( address.sin_addr ) << ":" << address.sin_port << endl;
    //                     close(new_fd);
    //                     exit(0);
    //                 }
    //                 if(i==1)
    //                 {
    //                     cout << "client " << inet_ntoa( address.sin_addr ) << ":" << address.sin_port << "# Sended at " << buffexp << "# Received at " << getDate() << endl;
    //                 }
    //                 else
    //                 {
    //                     cout << "client " << inet_ntoa( address.sin_addr ) << ":" << address.sin_port << "# " << buffexp << endl;
    //                 }
    //                 buffexp=strtok(NULL,"#");
    //             }
    //             if(-1==send(new_fd, msg_ack, strlen(msg_ack), 0))
    //             {
    //                 perror("Send ACK");
    //                 exit(1);
    //             }
    //         } // end while
    //     } // end fork
    //     close(new_fd); // parent doesn't need child listener
    } // end accept loop

    return 0;
}

void sigchld_handler(int s)
{
    while(wait(NULL)>0);
}