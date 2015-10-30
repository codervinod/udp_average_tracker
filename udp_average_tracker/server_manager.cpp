//
//  server_manager.cpp
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include <stdio.h>
#include "server_manager.h"
#include "ring_buffer.h"
#include "sqlite_store.h"
#include "udp_server.h"

#define AVG_INTERVAL 300

//5 min, each ping is not more than 1 sec apart + 200 sec for db latency
#define MAX_BUFFER 500

ServerManager *ServerManager::_inst = NULL;

ServerManager *ServerManager::inst()
{
    if(!_inst)
    {
        _inst = new ServerManager();
    }
    return _inst;
}

ServerManager::ServerManager()
:_current_sum(0),_current_count(0)
{
    _last_update_timestamp = 0;
}

void ServerManager::start(int port,std::string db_file)
{
    _pc = new RingBuffer<TimeValue>(MAX_BUFFER);
    _db_store = new SqLiteStore(db_file);
    if(_db_store->Connect())
    {
        _db_store->InitTables();
    }
    
    _run_consumer = true;
    _consumer_thread = std::thread(&ServerManager::consumer_runner, this);
    
    _server = new UdpServer(this,port);
}

void ServerManager::join()
{
    _server->join();
    _consumer_thread.join();
}

void ServerManager::end()
{
    join();
    _run_consumer = false;
}

ServerManager::~ServerManager()
{
    if(_pc)
        delete _pc;
    
    if(_db_store)
        delete _db_store;
    
    if(_server)
        delete _server;
}

void ServerManager::StoreValue(int value)
{
    TimeValue tv;
    tv._value =value;
    tv._timestamp = time(NULL);
    _pc->enqueue(tv);
}

void ServerManager::consumer_runner()
{
    while(_run_consumer)
    {
        TimeValue tv = _pc->dequeue();
        
        //Initialize first time
        if(_last_update_timestamp==0)
        {
            _last_update_timestamp =tv._timestamp;
        }
        
        //Store in the log table
        _db_store->SetVal(tv._timestamp,tv._value);
        
        //if 5 mins have elapsed since first update, update average
        if(tv._timestamp - _last_update_timestamp > AVG_INTERVAL)
        {
            _db_store->SetAverage(_last_update_timestamp+AVG_INTERVAL,
                                  (unsigned int)_current_sum/_current_count);
            _current_sum = 0;
            _current_count = 0;
            _last_update_timestamp = _last_update_timestamp+AVG_INTERVAL;
        }
        
        //update average computation
        _current_sum +=tv._value;
        ++_current_count;
    }
}