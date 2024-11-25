#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main(){
    int sockfd;
    char buffer[100];
    struct sockaddr_in broadcastaddr;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    broadcastaddr.sin_family = AF_INET;
    broadcastaddr.sin_addr.s_addr = inet_addr("255.255.255.255");   
    broadcastaddr.sin_port = htons(10000);

    int optval = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&optval,sizeof(int));

    while(1){
        printf("Message");
        fgets(buffer,100,stdin);
        sendto(sockfd,buffer,100,0,(struct sockaddr *) &broadcastaddr,sizeof(broadcastaddr));
        recvfrom(sockfd,buffer,100,0,NULL,NULL);
        printf("Recieved %s",buffer);
    }
    return 0;
}
