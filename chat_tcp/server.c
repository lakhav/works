#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    char buffer[100];

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); // Create socket

    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(22000);

    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)); // Bind socket
    listen(listen_fd, 10);                                           // Listen for connections
    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);      // Accept connection

    while (1)
    {
        bzero(buffer, 100);
        recv(comm_fd, buffer, 100, 0); // Receive message from client
        printf("Client: %s", buffer);
        fgets(buffer, 100, stdin);                // Server input
        send(comm_fd, buffer, strlen(buffer), 0); // Send message to client
    }

    close(comm_fd);
    close(listen_fd);
    return 0;
}
