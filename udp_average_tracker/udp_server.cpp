//
//  udp_server.cpp
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include "udp_server.h"
#include "server_manager.h"

#define BUFSIZE 4

UdpServer::UdpServer(ServerManager *sm,int port)
    :_port(port),
    _runner(&UdpServer::run,this),
    Server(sm)
{
}

UdpServer::~UdpServer()
{
    
}

void UdpServer::join(){
    _runner.join();
}

int UdpServer::run()
{
    struct sockaddr_in myaddr;      /* our address */
    struct sockaddr_in remaddr;     /* remote address */
    socklen_t addrlen = sizeof(remaddr);            /* length of addresses */
    size_t recvlen;                    /* # bytes received */
    int fd;                         /* our socket */
    unsigned char buffer[BUFSIZE];     /* receive buffer */
    
    /* create a UDP socket */
    
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket\n");
        return 0;
    }
    
    /* bind the socket to any valid IP address and a specific port */
    
    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(_port);
    
    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("bind failed");
        return 0;
    }
    
    /* now loop, receiving data and printing what we received */
    for (;;) {
        recvlen = recvfrom(fd, buffer, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
        printf("received %ld bytes\n", recvlen);
        if (recvlen > 0) {
            unsigned int *data=(unsigned int *)buffer;
            _sm->StoreValue(*data);
        }
    }
}