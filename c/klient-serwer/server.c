#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // close

#include <sys/socket.h> // socket
#include <string.h> // memset, strcspn
#include <sys/wait.h>
#include <signal.h> // sigaction
#include <netdb.h> // addrinfo

#include "config.h"

#define BUFFER 1024

char *cmdExec(char *cmd);
char *cmdRemote(char *command, char *type);
char *append(char *string1, char *string2);
void sigchld_handler(int s);

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sigaction sa;
    struct addrinfo hints, *result, *resi;
    struct sockaddr_storage client_addr;
    int yes=1;
    char client_ip[NI_MAXHOST];
    char client_port[NI_MAXSERV];
    char buffer[BUFFER]={0};
    char *buffresponse=malloc(sizeof(char));
    char *msg_welcome="Welcome client. Type 'exit' to quit.";

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

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags=AI_PASSIVE; // use all IP address
    hints.ai_family=AF_UNSPEC; // use IPv4 and IPv6
    hints.ai_socktype=SOCK_STREAM; // TCP

    if(getaddrinfo(NULL, appcfg->ptr_port, &hints, &result) != 0)
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

        if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes, sizeof(yes))) // fix to "Address already in use"
        {
            perror("Socket set option failed");
            exit(1);
        }

        if(0==bind(server_fd, resi->ai_addr, resi->ai_addrlen)) // if bind success
        {
            break;
        }

        close(server_fd);
    }

    freeaddrinfo(result);

    if(listen(server_fd, appcfg->max_connections))
    {
        perror("Listen");
        exit(1);
    }

    free(appcfg);

    printf("server# Waiting for connections\n");

    while(1) // accept loop
    {
        socklen_t addrlen=sizeof(client_addr);
        if((client_fd=accept(server_fd, (struct sockaddr *) &client_addr, &addrlen))<0)
        {
            perror("Accept");
            exit(1);
        }

        if(getnameinfo((struct sockaddr *) &client_addr, addrlen, client_ip, sizeof(client_ip), client_port, sizeof(client_port), 0) != 0)
        {
            perror("Getnameinfo");
            exit(1);
        }
        
        printf("server# Client connected from %s:%s\n", client_ip, client_port);

        switch(fork())
        {
            case 0: // child
                close(server_fd);

                if(-1==send(client_fd, msg_welcome, strlen(msg_welcome), 0)) // send welcome
                {
                    perror("Send");
                    exit(1);
                }

                while(1)
                {
                    memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
                    buffresponse=NULL;

                    if(-1==recv(client_fd, buffer, BUFFER, 0))
                    {
                        perror("Recv");
                        exit(1);
                    }
                    buffer[strcspn(buffer,"\r\n")]=0; // remove new line

                    printf("client# %s\n", buffer);    

                    buffresponse=cmdExec(buffer);

                    printf("server# %s\n", buffresponse);

                    if(-1==send(client_fd, buffresponse, strlen(buffresponse), 0))
                    {
                        perror("Send response");
                        exit(1);
                    }

                    switch(buffer[0])
                    {
                        case 'e':
                            close(client_fd);
                            exit(0);
                            break;
                    }
                } // end while
                break;

            default: // parent
                close(client_fd);
                break;
        } // end switch fork
    }

    return 0;
}

char *cmdExec(char *cmd)
{
    char *out=malloc(sizeof(char));
    out=NULL;

    int i=0;
    char *exp, *cmdarray[10], *cmdtmp;
    exp=strtok(cmd," ");
    while(exp!=NULL)
    {
        cmdarray[i]=exp;
        i++;
        exp=strtok(NULL," ");
    }

    switch(cmdarray[0][0])
    {
        case 'e': // exit
            out="Connection closed by client";
            break;

        case 'g': // get
            out="Incomplete command";
            switch(cmdarray[1][0])
            {
                case 'i': // interface
                    switch(i)
                    {
                        case 2:
                            out=cmdRemote("ls /sys/class/net | tr '\n' ' '", "r");
                            break;

                        case 4:
                            switch(cmdarray[3][0])
                            {
                                case 'i': // ip
                                    cmdtmp="ip addr show ";
                                    cmdtmp=append(cmdtmp, cmdarray[2]);
                                    cmdtmp=append(cmdtmp, " | grep inet | sed -r 's/.*inet6* //g' | sed -r 's/ .*//g' | tr '\n' ' '");
                                    out=cmdRemote(cmdtmp, "r");
                                    break;

                                case 'm': // mac
                                    cmdtmp="cat /sys/class/net/";
                                    cmdtmp=append(cmdtmp, cmdarray[2]);
                                    cmdtmp=append(cmdtmp, "/address | tr '\n' ' '");
                                    out=cmdRemote(cmdtmp, "r");
                                    break;

                                case 's': // status
                                    cmdtmp="cat /sys/class/net/";
                                    cmdtmp=append(cmdtmp, cmdarray[2]);
                                    cmdtmp=append(cmdtmp, "/operstate | tr '\n' ' '");
                                    out=cmdRemote(cmdtmp, "r");
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 's': // set
            out="Incomplete command";
            switch(cmdarray[1][0])
            {
                case 'i': // interface
                    switch(i)
                    {
                        case 5:
                            switch(cmdarray[3][0])
                            {
                                case 'm': // mac
                                    cmdtmp="ifconfig ";
                                    cmdtmp=append(cmdtmp, cmdarray[2]);
                                    cmdtmp=append(cmdtmp, " hw ether ");
                                    cmdtmp=append(cmdtmp, cmdarray[4]);
                                    out=cmdRemote(cmdtmp, "r");
                                    break;
                            }
                            break;

                        case 6:
                            switch(cmdarray[3][0])
                            {
                                case 'i': // [i]p
                                    switch(cmdarray[3][1])
                                    {
                                        case 'p': // i[p]
                                            switch(cmdarray[3][2])
                                            {
                                                case '4': // ip4
                                                    cmdtmp="ifconfig ";
                                                    cmdtmp=append(cmdtmp, cmdarray[2]);
                                                    cmdtmp=append(cmdtmp, " ");
                                                    cmdtmp=append(cmdtmp, cmdarray[4]);
                                                    cmdtmp=append(cmdtmp, " netmask ");
                                                    cmdtmp=append(cmdtmp, cmdarray[5]);
                                                    out=cmdRemote(cmdtmp, "r");
                                                    break;

                                                case '6': // ip6
                                                    cmdtmp="ifconfig ";
                                                    cmdtmp=append(cmdtmp, cmdarray[2]);
                                                    cmdtmp=append(cmdtmp, " inet6 add ");
                                                    cmdtmp=append(cmdtmp, cmdarray[4]);
                                                    cmdtmp=append(cmdtmp, "/");
                                                    cmdtmp=append(cmdtmp, cmdarray[5]);
                                                    out=cmdRemote(cmdtmp, "r");
                                                    break;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
    }

    if(out==NULL)
    {
        out="Invalid command";
    }

    return out;
}

char *cmdRemote(char *command, char *type)
{
    FILE *cmd;
    char line[100];
    char *fullline="";

    cmd=popen(command, type);
    if(!cmd)
    {
        perror("popen");
    }
    while(fgets(line,100,cmd))
    {
        fullline=append(fullline,line);
    }

    pclose(cmd);
    return fullline;
}

char *append(char *string1, char *string2)
{
    char *result=NULL;
    asprintf(&result, "%s%s", string1, string2);
    return result;
}

void sigchld_handler(int s)
{
    while(wait(NULL)>0);
}