#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create socket

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); // Connect to server

    while (1)
    {
        bzero(buffer, 100);
        fgets(buffer, 100, stdin);               // Client input
        send(sockfd, buffer, strlen(buffer), 0); // Send message to server
        recv(sockfd, buffer, 100, 0);            // Receive message from server
        printf("Server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
