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
char *cmdRemote(const char *command, const char *type);
void sigchld_handler(int s);

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sigaction sa;
    struct addrinfo hints, *result, *resi;
    struct sockaddr_storage client_addr;
    pid_t pid;
    pid_t return_pid; // return child pid status
    int yes=1;
    int status;
    int i; // iteration
    int active_connections=0;
    int max_connections=0;
    char client_ip[NI_MAXHOST];
    char client_port[NI_MAXSERV];
    char buffer[BUFFER]={0};
    char *buffresponse=NULL;
    char *msg_welcome="Welcome client. Type 'exit' to quit.";
    char *msg_too_many="Sorry, too many clients.";

    appconfig *appcfg=malloc(sizeof(appconfig));
    readConfig(appcfg, argv[1]);

    int forks[appcfg->max_connections]; // child pid array
    memset(forks, 0, appcfg->max_connections*sizeof(int));

    printf("Server config:\n");
    printf(" - port: %s\n", appcfg->ptr_port);
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

    free(appcfg->ptr_port);
    max_connections=appcfg->max_connections;
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

        active_connections++;

        if(getnameinfo((struct sockaddr *) &client_addr, addrlen, client_ip, sizeof(client_ip), client_port, sizeof(client_port), 0) != 0)
        {
            perror("Getnameinfo");
            exit(1);
        }
        
        printf("server# Client connected from %s:%s\n", client_ip, client_port);

        active_connections=1;
        for(i=0; i<max_connections; i++) // count active connections
        {
            if(forks[i]>0)
            {
                active_connections++;
                return_pid=waitpid(forks[i], &status, WNOHANG);
                if(0!=return_pid)
                {
                    active_connections--;
                    forks[i]=0;
                }
            }
        }
        if(active_connections<=max_connections)
        {
            printf("server# Connected clients %i/%i\n", active_connections, max_connections);
        }

        if(active_connections>max_connections) // limit connections and send message
        {
            printf("server# %s\n", msg_too_many);
            if(-1==send(client_fd, msg_too_many, strlen(msg_too_many), 0))
            {
                perror("Send");
                exit(1);
            }
            close(client_fd);
            continue;
        }

        pid=fork();
        switch(pid)
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

                    switch(buffer[0])
                    {
                        case 'e':
                            strcpy(buffresponse, "Bye!");
                            break;
                    }

                    if(-1==send(client_fd, buffresponse, strlen(buffresponse), 0))
                    {
                        perror("Send response");
                        exit(1);
                    }

                    free(buffresponse);

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
                for(i=0; i<max_connections; i++) // assign child pid to forks[]
                {
                    if(0==forks[i]) // empty, assign this child pid
                    {
                        forks[i]=pid;
                        break;
                    }
                    else // not empty, check child pid status
                    {
                        return_pid=waitpid(forks[i], &status, WNOHANG);
                        if(0!=return_pid)
                        {
                            forks[i]=pid;
                            break;
                        }
                    }
                }
                close(client_fd);
                break;
        } // end switch fork
    }

    return 0;
}

char *cmdExec(char *cmd)
{
    char *out_ptr=NULL;
    char out[BUFFER]={0};

    int i=0;
    char *exp, *cmdarray[10];
    char *cmdtmp_ptr=NULL;

    if(0!=strlen(cmd))
    {
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
                strcpy(out, "Connection closed by client");
                break;

            case 'g': // get
                strcpy(out, "Incomplete command");
                switch(cmdarray[1][0])
                {
                    case 'i': // interface
                        switch(i)
                        {
                            case 2:
                                memset(&out[0],0,sizeof(out));
                                out_ptr=cmdRemote("ls /sys/class/net | tr '\n' ' '", "r");
                                break;

                            case 4:
                                switch(cmdarray[3][0])
                                {
                                    case 'i': // ip
                                        memset(&out[0],0,sizeof(out));
                                        asprintf(&cmdtmp_ptr, "ip addr show %s | grep inet | sed -r 's/.*inet6* //g' | sed -r 's/ .*//g' | tr '\n' ' '", cmdarray[2]);
                                        out_ptr=cmdRemote(cmdtmp_ptr, "r");
                                        free(cmdtmp_ptr);
                                        break;

                                    case 'm': // mac
                                        memset(&out[0],0,sizeof(out));
                                        asprintf(&cmdtmp_ptr, "cat /sys/class/net/%s/address | tr '\n' ' '", cmdarray[2]);
                                        out_ptr=cmdRemote(cmdtmp_ptr, "r");
                                        free(cmdtmp_ptr);
                                        break;

                                    case 's': // status
                                        memset(&out[0],0,sizeof(out));
                                        asprintf(&cmdtmp_ptr, "cat /sys/class/net/%s/operstate | tr '\n' ' '", cmdarray[2]);
                                        out_ptr=cmdRemote(cmdtmp_ptr, "r");
                                        free(cmdtmp_ptr);
                                        break;
                                }
                                break;
                        }
                        break;
                }
                break;
            case 's': // set
                strcpy(out, "Incomplete command");
                switch(cmdarray[1][0])
                {
                    case 'i': // interface
                        switch(i)
                        {
                            case 5:
                                switch(cmdarray[3][0])
                                {
                                    case 'm': // mac
                                        asprintf(&cmdtmp_ptr, "ifconfig %s hw ether %s", cmdarray[2], cmdarray[4]);
                                        out_ptr=cmdRemote(cmdtmp_ptr, "r");
                                        free(cmdtmp_ptr);
                                        strcpy(out, "OK");
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
                                                        asprintf(&cmdtmp_ptr, "ifconfig %s %s netmask %s", cmdarray[2], cmdarray[4], cmdarray[5]);
                                                        out_ptr=cmdRemote(cmdtmp_ptr, "r");
                                                        free(cmdtmp_ptr);
                                                        strcpy(out, "OK");
                                                        break;

                                                    case '6': // ip6
                                                        asprintf(&cmdtmp_ptr, "ifconfig %s inet6 add %s/%s", cmdarray[2], cmdarray[4], cmdarray[5]);
                                                        out_ptr=cmdRemote(cmdtmp_ptr, "r");
                                                        free(cmdtmp_ptr);
                                                        strcpy(out, "OK");
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
    }

    if(NULL==out_ptr)
    {
        out_ptr=calloc(BUFFER, sizeof(char));
        strcpy(out_ptr, "Invalid command");
    }
    if(0!=strlen(out))
    {
        strcpy(out_ptr, out);
    }

    return out_ptr;
}

char *cmdRemote(const char *command, const char *type)
{
    FILE *cmd;
    char line[100];
    char *fullline=calloc(BUFFER, sizeof(char));

    cmd=popen(command, type);
    if(!cmd)
    {
        perror("popen");
    }
    while(fgets(line,100,cmd))
    {
        strcat(fullline, line);
    }

    pclose(cmd);
    return fullline;
}

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG)>0);
}