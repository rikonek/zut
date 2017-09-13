//  - Czat - Wysyłam wiadomość, serwer 
// http://www.boost.org/doc/libs/1_64_0/doc/html/boost_asio.html

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

// #include <stdio.h>
#include <sys/socket.h> // socket
// #include <stdlib.h>
#include <netinet/in.h> // sockaddr_in
// #include <string.h>
#include <ctime>
#include <unistd.h> // usleep

using namespace std;

void server(const int port, const int max_connections);
char *getDate();

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
        options.add_options("Server")
            ("m,max-connections", "Maximum of concurrent connections", cxxopts::value<int>()->default_value("5"));

        options.parse(argc, argv);

        if(options.count("help"))
        {
            cout << options.help({"", "Server"}) << endl;
            exit(0);
        }

        if(options.count("client") && options.count("server"))
        {
            cout << "Can't start client and server together." << endl;
            exit(0);
        }

        if(options.count("client"))
        {
            cout << "Client starting..." << endl;
        }

        if(options.count("server"))
        {
            cout << "Server config:" << endl;
            cout << "- port: " << options["port"].as<int>() << endl;
            cout << "- max-connections: " << options["max-connections"].as<int>() << endl;
            cout << "Server starting..." << endl;
            // cout << "Listen..." << endl;
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

void server(const int port, const int max_connections)
{
    int server_fd, new_fd;
    struct sockaddr_in address;
    int yes=1;

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

    char *msg_welcome = "server# Welcome client";
    char buffer[1024]={0};
    char *msg_ack="server# The message was delivered";

    while(1) // accept loop
    {
        int addrlen=sizeof(address);
        if((new_fd=accept(server_fd, (struct sockaddr *) &address, (socklen_t*) &addrlen))<0)
        {
            perror("Accept");
            exit(1);
        }

        if(!fork())
        {
            close(server_fd); // child dosen't need listener
            if(-1==send(new_fd, msg_welcome, strlen(msg_welcome), 0))
            {
                perror("Send");
            }
            cout << "client# Client ID " << new_fd << " connected" << endl;

            while(1)
            {
                recv(new_fd, buffer, 1024, 0);
                if(strcmp(buffer,"exit\r\n")==0)
                {
                    cout << "client# Connection closed" << endl;
                    close(new_fd);
                    exit(0);
                }
                else
                {
                    cout << "Receive at " << getDate() << " from client ID " << new_fd << " # " << buffer;
                    send(new_fd, msg_ack, strlen(msg_ack), 0);
                    memset(&buffer[0],0,sizeof(buffer)); // clear old buffer
                }
            }
        } // end fork
        close(new_fd); // parent dosen't need listener
    } // end accept loop
}

char *getDate()
{
    time_t now=time(0); // current date/time
    char *dt=ctime(&now); // time to string convert
    dt[strlen(dt)-1]=0; // remove new line
    return dt;
}