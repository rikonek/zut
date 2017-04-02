#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fd[2], nbytes;
	pid_t childpid;
	char string[]="Hello_world!\n";
	char readbuffer[80];
	pipe(fd);
	if((childpid=fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if(childpid==0)
	{
// Proces potomny - Wpisuje string do pipe
// fd[0] - do odczytu
// fd[1] - do zapisu
		close(fd[0]);
		write(fd[1],string,(strlen(string)+1));
		exit(0);
	}
	else
	{
// Proces rodzica - Odczytuje string z pipe
		close(fd[1]);
		nbytes=read(fd[0],readbuffer,sizeof(readbuffer));
		printf("Received... string: %s",readbuffer);
	}
	return 0;
}
