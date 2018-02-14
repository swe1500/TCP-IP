#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Data{
    int ID;
    float dist, angle, vel;
};

int main()
{
    int    listenfd, connfd;
    struct sockaddr_in     servaddr;
    char   buff[16];
    int    n;
//    int ID;
//    float dist ,angle ,vel;
    vector<Data> RadarDataTable;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
    printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }

    if( listen(listenfd, 10) == -1){
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }

    printf("======waiting for client's request======\n");
    if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
    }
    while(1){
    Data data;
    n = read(connfd,&buff,sizeof(buff));
    memcpy(&data.ID, buff, 4);
    memcpy(&data.dist, buff+4, 4);
    memcpy(&data.angle, buff+8, 4);
    memcpy(&data.vel, buff+12, 4);
    if(data.ID == 1)
        RadarDataTable.clear();
    RadarDataTable.push_back(data);


    }
    close(connfd);
    close(listenfd);
}
