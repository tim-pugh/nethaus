#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    if(argc < 3) {
        printf("Not enough arguments provided. Exiting..\n");
        exit(0);
    }

    struct in_addr argvIp;  //ip address
    struct hostent *server; //server
    int sockPuppet = socket(AF_INET, SOCK_STREAM, 0);
    int port = atoi(argv[2]);  //socket and port
    struct sockaddr_in serverIp;
    socklen_t lengthServerIp = sizeof(serverIp);

    inet_pton(AF_INET, argv[1], &argvIp);

    server = gethostbyaddr(&argvIp, sizeof argvIp, AF_INET);

    if(server == NULL) {
        printf("Could not verify host. Exiting..\n");
        exit(0);
    }

    if(sockPuppet < 0){
        printf("Could not open socket!\n");
    }

    memset(&serverIp, 0, lengthServerIp);   //frombzero to memset
    serverIp.sin_family = AF_INET;
    memcpy((char *) server->h_addr_list[0], (struct sockaddr*)&serverIp.sin_addr.s_addr, server->h_length); //from bcopy to memcopy

    serverIp.sin_port = htons(port);


   return 0;
}
