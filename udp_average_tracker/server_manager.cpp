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

#define MAX_BUFFER 300 //5 min, each ping is not more than 1 sec apart

ServerManager *ServerManager::_inst = NULL;

ServerManager *ServerManager::inst()
{
    if(!_inst)
    {
        _inst = new ServerManager();
    }
    return _inst;
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
    
    _server->join();
    _consumer_thread.join();
}

void ServerManager::end()
{
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
        
        //Store in the log table
        _db_store->SetVal(tv._timestamp,tv._value);
        
        //update average computation
        
        //if 5 mins have elapsed since first update, update average
        
    }
}