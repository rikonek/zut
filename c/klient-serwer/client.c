#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // close

#include <sys/socket.h> // socket
#include <string.h> // memset, strcspn
#include <netdb.h> // addrinfo

#define BUFFER 1024

void printUsage(char *exe);
void printHelp();

int main(int argc, char *argv[])
{
    int server_fd;
    struct addrinfo hints, *result, *resi;
    char buffer[BUFFER]={0};
    char ip[INET6_ADDRSTRLEN]="127.0.0.1"; // ip[46] - ipv6 with ipv4 tunneling
    char *port=NULL;
    
    port="7777";

    if(argc>1) // one argument
    {
        if(strcmp(argv[1], "--help")==0)
        {
            printUsage(argv[0]);
            exit(0);
        }

        strcpy(ip,argv[1]); // set ip from cmd
    }
    if(argc>2) // two arguments
    {
        port=argv[2];
    }
    if(argc>3) // more than two arguments
    {
        printUsage(argv[0]);
        exit(0);
    }

    printf("Client config:\n");
    printf(" - host: %s\n", ip);
    printf(" - port: %s\n", port);
    printf("Client starting... Type 'help' or 'exit'.\n");

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family=AF_UNSPEC; // use IPv4 and IPv6
    hints.ai_socktype=SOCK_STREAM; // TCP

    if(getaddrinfo(ip, port, &hints, &result) != 0)
    {
        perror("getaddrinfo");
        exit(1);
    }

    for(resi=result; resi!=NULL; resi=resi->ai_next) // bind to first interface
    {
        server_fd=socket(resi->ai_family, resi->ai_socktype, resi->ai_protocol);
        if(-1==server_fd)
        {
            continue; // if error try next address
        }

        if(0==connect(server_fd, resi->ai_addr, resi->ai_addrlen)) // if connect success
        {
            break;
        }
    }

    freeaddrinfo(result);
    
    // receive hello from server
    memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
    if(-1==recv(server_fd, buffer, BUFFER, 0))
    {
        perror("Recv");
        exit(1);
    }
    printf("server# %s\n", buffer);

    if(strcmp(buffer, "Sorry, too many clients.")==0)
    {
        close(server_fd);
        exit(0);
    }

    while(1)
    {
        printf("client# ");
        memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
        fgets(buffer, BUFFER, stdin);
        buffer[strcspn(buffer,"\r\n")]=0; // remove new line
        switch(buffer[0])
        {
            case 'h': // help
                printHelp();
                continue;
        }
        if(-1==send(server_fd, buffer, BUFFER, 0))
        {
            perror("Send");
            exit(1);
        }

        // read response
        memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
        if(-1==recv(server_fd, buffer, BUFFER, 0))
        {
            perror("Recv");
            exit(1);
        }
        buffer[strcspn(buffer,"\r\n")]=0; // remove new line
        printf("server# %s\n", buffer);

        if(strcmp(buffer, "Bye!")==0)
        {
            close(server_fd);
            exit(0);
        }
    }

    return 0;
}

void printUsage(char *exe)
{
    printf("Usage %s <ip> <port>\n", exe);
}

void printHelp()
{
    printf("Commands:\n");
    printf(" - exit \t\t\t\t\t Exit\n");
    printf(" - get interface \t\t\t\t Show all interfaces\n");
    printf(" - get interface <name> ip \t\t\t Show interface ip address\n");
    printf(" - get interface <name> mac \t\t\t Show interface hardware address\n");
    printf(" - get interface <name> status \t\t\t Show interface status (up/down)\n");
    printf(" - help \t\t\t\t\t Show this help\n");
    printf(" - set interface <name> mac <mac address> \t Set interface hardware address\n");
    printf(" - set interface <name> ip4 <ip> <netmask> \t Set interface IPv4 address and mask\n");
    printf(" - set interface <name> ip6 <ip> <netmask> \t Set interface IPv6 address and mask\n");
}