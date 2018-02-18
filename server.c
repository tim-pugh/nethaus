#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

void main(int argc, char * argv[]) {
    if(argc < 2){
        printf("Not enough arguments. System exiting..");
        exit(0);
    }
    //socket creation
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) printf("Could not open socket!!\n");
    //host to server setup
    struct sockaddr_in server, from;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    //binding
    if(bind(sock,(struct sockaddr*) &server, sizeof(server)) < 0) printf("Error binding!!\n");

    //recieving handshake
    char buffer[1024];
    socklen_t fromLength = sizeof(from);

    recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&from, &fromLength);
    printf("%s", buffer);


}

