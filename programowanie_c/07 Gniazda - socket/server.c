#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
	int sock;
	int client_sock;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	char *mysocket="/tmp/mysocket";

// usuwam stary socket bo inaczej skrypt sie nie uruchomi
	unlink(mysocket);

	sock=socket(AF_UNIX,SOCK_STREAM,0);
	if(sock==-1)
	{
		perror("Blad otworzenia socketu");
		exit(0);
	}

	server_address.sun_family=AF_UNIX;
	strncpy(server_address.sun_path,mysocket,sizeof(server_address.sun_path));

	if( bind(sock,(struct sockaddr *)&server_address, sizeof(server_address)) )
	{
		perror("Blad: binding stream socket");
		exit(0);
	}

	printf("Socket has name %s\n",server_address.sun_path);

	listen(sock,5);
	while(1)
	{
		char ch;
		printf("Serwer oczekuje\n");

		client_sock=accept(sock,(struct sockaddr *)&client_address,sizeof(client_address));

		read(client_sock,&ch,1);
		ch++;
		write(client_sock,&ch,1);
		close(client_sock);
	}

	close(sock);

	return 0;
}
