#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in localSock;
struct ip_mreq group;
int sd;
int datalen;
char databuf[1024];

int main(int argc, char *argv[])
{

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        perror("Opening datagram socket");
        exit(1);
    }

    int reuse = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
    {
        perror("Setting SO_REUSEADDR");
        close(sd);
        exit(1);
    }

    memset((char *)&localSock, 0, sizeof(localSock));
    localSock.sin_family = AF_INET;
    localSock.sin_port = htons(5555);
    localSock.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *)&localSock, sizeof(localSock)) < 0)
    {
        perror("Binding datagram socket");
        close(sd);
        exit(1);
    }

    group.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
    group.imr_interface.s_addr = INADDR_ANY;

    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
    {
        perror("Adding multicast group");
        close(sd);
        exit(1);
    }

    datalen = sizeof(databuf);
    if (recvfrom(sd, databuf, datalen, 0, NULL, NULL) < 0)
    {
        perror("Reading datagram message");
        close(sd);
        exit(1);
    }

    printf("Received message: %s\n", databuf);

    close(sd);

    return 0;
}
