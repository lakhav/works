// sending data
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct in_addr localInterface;
struct sockaddr_in groupSock;
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

    memset((char *)&groupSock, 0, sizeof(groupSock));
    groupSock.sin_family = AF_INET;
    groupSock.sin_addr.s_addr = inet_addr("225.1.1.1");
    groupSock.sin_port = htons(5555);

    char loopch = 0;
    if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, &loopch, sizeof(loopch)) < 0)
    {
        perror("Setting IP_MULTICAST_LOOP:");
        close(sd);
        exit(1);
    }

    localInterface.s_addr = inet_addr("9.5.1.1"); // Local interface IP address
    if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &localInterface, sizeof(localInterface)) < 0)
    {
        perror("Setting local interface");
        close(sd);
        exit(1);
    }

    snprintf(databuf, sizeof(databuf), "Hello, Multicast Group!");

    datalen = strlen(databuf);

    if (sendto(sd, databuf, datalen, 0, (struct sockaddr *)&groupSock, sizeof(groupSock)) < 0)
    {
        perror("Sending datagram message");
        close(sd);
        exit(1);
    }

    printf("Message sent to the multicast group: %s\n", databuf);

    close(sd);
    return 0;
}
