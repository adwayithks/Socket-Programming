#include<stdio.h>
#include <sys/socket.h>
#include<sys/types.h>
#include <string.h>

// #include <fcntl.h>
// #include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
void main() 
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == -1)
    {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }

    // struct sockaddr_in addr;
    // addr.sin_family = AF_INET;
    // addr.sin_addr.s_addr = INADDR_ANY;
    // addr.sin_port = htons(8080); // Use any available port
    struct sockaddr_in addr = {
        AF_INET,
        0x901f,
        0
    };

    if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) 
    {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }

    if(listen(s, 10) == -1)
    {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }


    int client_fd;

    while(1)
    {
        if(client_fd = accept(s, 0, 0))
        {
            printf("connection accepted");
            char buffer[256] = {0};
            recv(client_fd, buffer, 256, 0);

            // GET /file.html .....

            char response[] ="HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "\r\n"
                        "<html><body><h1>HTTP OK</h1></body></html>";

            send(client_fd,response,strlen(response),0);
        }
    }
}
