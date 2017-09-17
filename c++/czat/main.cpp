// - Zaimplementować prosty "czat" międzyprocesowy.
//     1. Klient - łączy się wybranym sposobem z serwerem, przesyła mu wiadomości
//        zawierające następujące dane:
//         1. Czas nadania wiadomości.
//         2. Identyfikator nadawcy.
//         3. Wiadomość.
//     2. Serwer - przyjmuje połączenia:
//         1. Wypisuje następujące informacje na standardowe wyjście albo do pliku:
//             1. Czas nadania wiadomości.
//             2. Czas odebrania wiadomości.
//             3. Identyfikator nadawcy.
//             4. Wiadomość.
//         2. Wysyła potwierdzenie odebrania wiadomości do klienta.
//         3. Rozsyła otrzymane wiadomości do połączonych klientów. (* nadobowiązkowe)

#include <iostream>
#include "cxxopts.hpp"

#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <string.h> // strcspn
#include <ctime>
#include <unistd.h> // usleep
#include <arpa/inet.h> // inet_ntoa
#include <sys/wait.h>
#include <signal.h> // sigaction

using namespace std;

void client(const std::string ip, const int port);
void server(const int port, const int max_connections);
char *getDate();
void sigchld_handler(int s);
char *append(char *string1, char *string2);

int main(int argc, char *argv[])
{
    try
    {
        cxxopts::Options options(argv[0], "Simple interprocess chat");
        options.add_options()
            ("c,client", "Start client")
            ("h,help", "Print this help")
            ("p,port", "Port number", cxxopts::value<int>()->default_value("7777"))
            ("s,server", "Start server");
        options.add_options("Client")
            ("d,destination", "Destination IP address", cxxopts::value<std::string>()->default_value("127.0.0.1"));
        options.add_options("Server")
            ("m,max-connections", "Maximum of concurrent connections", cxxopts::value<int>()->default_value("5"));

        options.parse(argc, argv);

        if(options.count("help"))
        {
            cout << options.help({"", "Client", "Server"}) << endl;
            exit(0);
        }

        if(options.count("client") && options.count("server"))
        {
            cout << "Can't start client and server together." << endl;
            exit(0);
        }

        if(options.count("client"))
        {
            cout << "Client starting... Type 'exit' to quit." << endl;
            client(options["destination"].as<std::string>(),options["port"].as<int>());
        }

        if(options.count("server"))
        {
            cout << "Server config:" << endl;
            cout << "- port: " << options["port"].as<int>() << endl;
            cout << "- max-connections: " << options["max-connections"].as<int>() << endl;
            cout << "Server starting..." << endl;
            server(options["port"].as<int>(),options["max-connections"].as<int>());
        }
    }
    catch(const cxxopts::OptionException &e)
    {
        cout << e.what() << endl;
        cout << "Try using '" << argv[0] << " --help' to display usage info." << endl;
        exit(1);
    }

    return 0;
}

void client(const std::string xip, const int port)
{
    int server_fd;
    struct sockaddr_in address;
    char ip[16]={0};
    strcpy(ip,xip.c_str());

    char buffer[1024]={0};

    server_fd=socket(AF_INET, SOCK_STREAM, 0); // create socket
	if(-1==server_fd)
	{
		perror("Socket create failed");
		exit(1);
    }

    address.sin_family=AF_INET;
    address.sin_port=htons(port); // host to network short // 0 for random port
    memset(&(address.sin_zero),0,8); // sin_zero set to 0

    if(inet_pton(AF_INET, ip, &address.sin_addr)<=0) // convert IP to binary
    {
        perror("Invalid address");
        exit(1);
    }

    if(connect(server_fd, (struct sockaddr *) &address, sizeof(address)))
    {
        perror("Connection failed");
        exit(1);
    }

    // receive hello from server
    memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
    if(-1==recv(server_fd, buffer, 1024, 0))
    {
        perror("Recv");
        exit(1);
    }
    cout << "server# " << buffer << endl;

    while(1)
    {
        cout << "client# ";
        memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer,"\r\n")]=0; // remove new line
        memcpy(buffer,append("#", buffer), sizeof(buffer));
        memcpy(buffer,append(getDate(), buffer), sizeof(buffer));

        if(-1==send(server_fd, buffer, strlen(buffer), 0))
        {
            perror("Send");
            exit(1);
        }

        char *buffexp;
        buffexp=strtok(buffer,"#");
        while(buffexp!=NULL)
        {
            if(strcmp(buffexp,"exit")==0)
            {
                close(server_fd);
                exit(0);
            }
            buffexp=strtok(NULL,"#");
        }

        // receive ACK
        memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
        if(-1==recv(server_fd, buffer, 1024, 0))
        {
            perror("Recv");
            exit(1);
        }
        buffer[strcspn(buffer,"\r\n")]=0; // remove new line
        cout << "server# " << buffer << endl;
    } // while end
}

void server(const int port, const int max_connections)
{
    int server_fd, new_fd;
    int yes=1;
    struct sockaddr_in address;
    struct sigaction sa;

    char buffer[1024]={0};
    char *msg_welcome = "Welcome client. Type 'exit' to quit.";
    char *msg_ack="The message was delivered";

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

    cout << "server# Waiting for connections" << endl;

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
        cout << "client# Client connected from " << inet_ntoa( address.sin_addr ) << ":" << address.sin_port << endl;

        if(!fork())
        {
            // child process
            close(server_fd); // child doesn't need listener
            if(-1==send(new_fd, msg_welcome, strlen(msg_welcome), 0))
            {
                perror("Send");
                exit(1);
            }

            while(1)
            {
                memset(&buffer[0],0,sizeof(buffer)); // clear old buffer                
                if(-1==recv(new_fd, buffer, 1024, 0))
                {
                    perror("Recv");
                    exit(1);
                }
                buffer[strcspn(buffer,"\r\n")]=0; // remove new line

                int i=0;
                char *buffexp;
                buffexp=strtok(buffer,"#");
                while(buffexp!=NULL)
                {
                    i++;
                    if(strcmp(buffexp,"exit")==0)
                    {
                        cout << "client# Connection closed by client " << inet_ntoa( address.sin_addr ) << ":" << address.sin_port << endl;
                        close(new_fd);
                        exit(0);
                    }
                    if(i==1)
                    {
                        cout << "client " << inet_ntoa( address.sin_addr ) << ":" << address.sin_port << "# Sended at " << buffexp << "# Received at " << getDate() << endl;
                    }
                    else
                    {
                        cout << "client " << inet_ntoa( address.sin_addr ) << ":" << address.sin_port << "# " << buffexp << endl;
                    }
                    buffexp=strtok(NULL,"#");
                }
                if(-1==send(new_fd, msg_ack, strlen(msg_ack), 0))
                {
                    perror("Send ACK");
                    exit(1);
                }
            } // end while
        } // end fork
        close(new_fd); // parent doesn't need child listener
    } // end accept loop
}

char *getDate()
{
    time_t now=time(0); // current date/time
    char *dt=ctime(&now); // time to string convert
    dt[strlen(dt)-1]=0; // remove new line
    return dt;
}

void sigchld_handler(int s)
{
    while(wait(NULL)>0);
}

char *append(char *string1, char *string2)
{
    char *result=NULL;
    asprintf(&result, "%s%s", string1, string2);
    return result;
}