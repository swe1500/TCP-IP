#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>
#include <linux/can.h>
#include <sstream>

#define MAXLINE 4096

using namespace std;
template <typename T>
string Num2String(T num){
	ostringstream buff;
	buff<<num;
	return buff.str();
}

void CopyString(char* sendline, string str){
    int i =0;	
    for(; i < str.size(); i++)
	sendline[i] = str[i];
    	sendline[i]='\n';
}

int main(int argc, char** argv)
{
    int    sockfd, n;
    int a = 4321;
    char    recvline[4096], sendline[4096];
    struct sockaddr_in    servaddr;
    string str = Num2String(a);

    if( argc != 2){
    printf("usage: ./client <ipaddress>\n");
    exit(0);
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
    printf("inet_pton error for %s\n",argv[1]);
    exit(0);
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }

    //printf("send msg to server: \n");
    //fgets(sendline, 4096, stdin);

    while(1){
	CopyString(sendline, str);
        send(sockfd,sendline,str.size()+1,0);
        //printf("1212\n");
    }
    /****
    if( send(sockfd, sendline, strlen(sendline), 0) < 0)
    {
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
    exit(0);
    }
    ****/

    close(sockfd);
    exit(0);
}
