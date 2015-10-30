//
//  udp_server.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef __udp_average_tracker__udp_server__
#define __udp_average_tracker__udp_server__

#include <stdio.h>
#include <thread>
#include "server.h"

class ServerManager;

class UdpServer:public Server
{
public:
    UdpServer(ServerManager *sm,int port);
    virtual ~UdpServer();
    int run();
    void join();
private:
    int _port;
    std::thread _runner;
    
};

#endif /* defined(__udp_average_tracker__udp_server__) */
