//
//  main.cpp
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include <iostream>

#include "server_manager.h"

int main(int argc, const char * argv[]) {
    
    ServerManager::inst()->start(1153,"avg_tracker.db");
    
    return 0;
}
