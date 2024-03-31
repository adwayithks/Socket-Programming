#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT 1731
#define MAX_PENDING 5
#define MAX_LINE 256

int main()
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int buf_len, addr_len;
	int s, new_s,len;
	
	/* build address data structure */
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);
	
	/* setup passive open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
	{
		perror("simplex-talk: socket");
		exit(1);
	}
	/* bind the socket to a port */
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) 
	{
		perror("simplex-talk: bind");
		exit(1);
	}
	
	/*listen for a connection*/
	listen(s, MAX_PENDING);
	
	/* wait for connection, then receive and print text */
	while(1) 
	{
		if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0)
		{
			perror("simplex-talk: accept");
			exit(1);
		}
		
		while (buf_len = recv(new_s, buf, sizeof(buf), 0))
		{
			printf("client : ");
			fputs(buf, stdout);

			printf("Server : ");
			fgets(buf, 256, stdin);
			buf[MAX_LINE-1] = '\0';
			len = strlen(buf) + 1;
			send(new_s, buf, buf_len, 0);
		}
		close(new_s);
	}

	return 0;
}
