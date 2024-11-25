#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int sockfd;
    char buffer[100];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(22000);

    // Bind the socket to the specified address and port
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);

    // Chat loop
    while (1)
    {
        // Receive message from client
        bzero(buffer, 100);
        recvfrom(sockfd, buffer, 100, 0, (struct sockaddr *)&cliaddr, &len);
        printf("Client: %s", buffer);

        // Server input
        bzero(buffer, 100);
        printf("Server: ");
        fgets(buffer, 100, stdin);

        // Send message to client
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, len);
    }

    close(sockfd);
    return 0;
}
