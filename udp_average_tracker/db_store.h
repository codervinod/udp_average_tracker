//
//  db_store.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef udp_average_tracker_db_store_h
#define udp_average_tracker_db_store_h

class DbStore{
public:
    DbStore() {}
    virtual ~DbStore() {}
    virtual bool Connect() = 0;
    virtual bool InitTables() = 0;
    virtual bool SetVal(time_t time,unsigned int value) = 0;
    virtual bool SetAverage(time_t time,unsigned int value) = 0;

};

#endif
