#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    char sendline[100], recvline[100];
    struct sockaddr_in servaddr;
    socklen_t len;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize server address structure
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Client loop
    while (1)
    {
        bzero(sendline, 100);
        bzero(recvline, 100);

        fgets(sendline, 100, stdin); // Read input from the user

        len = sizeof(servaddr);

        // Send message to the server
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, len);

        // Receive echoed message from the server
        recvfrom(sockfd, recvline, 100, 0, NULL, NULL);

        printf("%s", recvline);
    }
    return 0;
}