#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100];
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Initialize server address structure
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);

    // Bind the socket to the address and port
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Server loop
    while (1) {
        len = sizeof(cliaddr);
        bzero(buffer, sizeof(buffer));

        // Receive message from client
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);

        printf("Echoing back - %s", buffer);

        // Send the same message back to client (echo)
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, len);
    }

    return 0;
}

