/*======================================================
    > File Name: data_accumulated_client.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年11月22日 星期日 22时09分50秒
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
    if(connect(sockfd,(struct sockaddr *)&address,sizeof(address)) < 0)
    {
        printf("连接失败\n");
    }

    char data[50] = "hahahhahahahhahahahhaha";
    while(1)
    {
        printf("发送");
        send(sockfd,data,strlen(data),0);   
    }

  return 0;
}
