//
//  main.cpp
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include <iostream>

#include "udp_server.h"
#include "db_store.h"
#include <time.h>

int main(int argc, const char * argv[]) {
    
    UdpServer udp_server(1153);
    DbStore db_store("avg_tracker.db");
    
    if(db_store.Connect()){
        db_store.InitTables();
    }
    
    
    db_store.SetVal(time(NULL),3);
    db_store.SetAverage(time(NULL),33);
    udp_server.join();
    return 0;
}
