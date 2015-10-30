//
//  db_store.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef __udp_average_tracker__db_store__
#define __udp_average_tracker__db_store__

#include <stdio.h>
#include <string>
#include "sqlite3.h"
#include <time.h>
class DbStore{
public:
    DbStore(std::string store);
    virtual ~DbStore();
    bool Connect();
    bool InitTables();
    bool SetVal(time_t time,unsigned int value);
    bool SetAverage(time_t time,unsigned int value);
private:
    bool ExecQuery(std::string sql);
    std::string _store;
    sqlite3 *_db;
};

#endif /* defined(__udp_average_tracker__db_store__) */
