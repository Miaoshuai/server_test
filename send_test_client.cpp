/*======================================================
    > File Name: send_test_client.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年11月30日 星期一 18时15分08秒
 =======================================================*/

#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



int main(int argc,char **argv)
{
    if(argc <= 2)
    {
        printf("参数有误\n");
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port = htons(port);

    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    //设置发送套接字的伐值
    int lowat = 5000;
    int len = sizeof(lowat);
    setsockopt(sockfd,SOL_SOCKET,SO_SNDLOWAT,&lowat,sizeof(len));
    //设置发送缓冲区的大小
    int sndbuf = 4000;
    len = sizeof(sndbuf);
    setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sndbuf,sizeof(len));
    if(connect(sockfd,(struct sockaddr *)&address,sizeof(address)) < 0)
    {
        printf("连接失败\n");
    }

     char buf[2048] = "hello,world\n";
     int ret = write(sockfd,buf,strlen(buf));
     printf("已发送的字节数:%d\n",ret);
     close(sockfd);
    
     return 0;
}
