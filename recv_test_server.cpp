/*======================================================
    > File Name: recv_test_server.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年11月30日 星期一 10时22分17秒
 =======================================================*/

#include <stdio.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Buffer.h>
#include <string>
#include <iostream>
#include <muduo/base/StringPiece.h>

//新来连接和其断开时调用
void connectionCallback(const muduo::net::TcpConnectionPtr &conn)
{
    printf("连接建立\n");
    conn->send("hello,world\n");
    printf("发送完成\n");
    
}



int main(int argc,char **argv)
{
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(argv[1],static_cast<uint16_t>(atoi(argv[2])));
    
    muduo::net::TcpServer server(&loop,listenAddr,"tcpServer",muduo::net::TcpServer::kReusePort);  //设置为重用端口
    //设置给新连接的各种回调
    server.setConnectionCallback(connectionCallback);

    server.start();
       
    loop.loop();

    return 0;
}
