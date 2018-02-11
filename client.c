#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "sendrecieve.h"
#include <time.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <pthread.h>
#include <unistd.h>

void main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Not enough arguments provided. Exiting..\n");
       exit(0);
    };

    int sock = socket(AF_INET, SOCK_DGRAM, 0); //socket
    struct sockaddr_in server, incoming;
    struct in_addr argvIp;
    inet_pton(AF_INET, argv[1], &argvIp.s_addr);
    struct hostent *serverHostName = gethostbyaddr(&argvIp, sizeof argvIp, AF_INET); //less deprecated then getbyhostname, and less confusing then its successor

    if(serverHostName == NULL) {
        printf("Could not verify host. Exiting..\n");
        exit(0);
    };

    char HostName[256];
    gethostname(HostName, sizeof(HostName));
    char * ipAddy= inet_ntoa(*((struct in_addr *)serverHostName->h_addr_list[0]));
    printf("Host Server: %s  and its IP: %s\n", HostName, ipAddy);

    if(sock < 0)
        printf("Could not open socket!!\n");

    memset(&server, 0, sizeof(server));   //making server var. NULL
    server.sin_family = AF_INET;    //setting it's attributes
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]); //placing in IP address

    memcpy((char *) serverHostName->h_addr_list[0], (struct sockaddr*)&server.sin_addr.s_addr, serverHostName->h_length); //from bcopy to memcopy. memcopy


    p = malloc(sizeof(struct payload));
    p->port = atoi(argv[2]);   //header port
    inet_pton(AF_INET, argv[1], &p->ip);  //header ip
    p->anyFileType = &argv[3];

    //struct serialize *dataSerialized;
    //dataSerialized = malloc(sizeof (struct serialize));

    char b = serialize3();

   clock_t start = clock();
   clock_t end = clock() - start;

    //char buffer[1024];
    //strcpy(buffer, "HELLO THIS IS A SIMPLE TEST!");
    //sendto(sock, buffer, 1024, 0, (struct sockaddr*)&serverIp, sizeof(serverIp));


}



