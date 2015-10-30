//
//  server_manager.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef udp_average_tracker_server_manager_h
#define udp_average_tracker_server_manager_h

#include <string>
#include <thread>
#include "producer_consumer.h"
#include "time_value.h"

class Server;
class DbStore;


class ServerManager
{
public:
    static ServerManager *inst();
    virtual ~ServerManager();
    
    
    void start(int port,std::string db_file);
    void end();
    void StoreValue(int value);
    void join();
private:
    void consumer_runner();
    static ServerManager *_inst;
    ServerManager();
    DbStore *_db_store;
    Server *_server;
    ProducerConsumer<TimeValue> *_pc;
    std::thread _consumer_thread;
    bool _run_consumer;
    time_t _last_update_timestamp;
    size_t _current_sum,_current_count;
};

#endif
