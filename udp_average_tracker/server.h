//
//  server.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef udp_average_tracker_server_h
#define udp_average_tracker_server_h

#include "server_manager.h"


class Server
{
public:
    Server(ServerManager *sm):_sm(sm)
    {
        
    }
    virtual ~Server() {}
    virtual int run() = 0;
    virtual void join() = 0;
protected:
    ServerManager *_sm;
};

#endif
