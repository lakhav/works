#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    char buffer[100];
    struct sockaddr_in servaddr;
    socklen_t len;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(servaddr);

    // Chat loop
    while (1) {
        // Client input
        bzero(buffer, 100);
        printf("Client: ");
        fgets(buffer, 100, stdin);

        // Send message to server
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, len);

        // Receive message from server
        bzero(buffer, 100);
        recvfrom(sockfd, buffer, 100, 0, NULL, NULL);
        printf("Server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
