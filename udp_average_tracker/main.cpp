//
//  main.cpp
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include "server_manager.h"
#include <iostream>
int main(int argc, const char * argv[]) {
    
    if(argc<3){
        fprintf(stderr,"Usage udp_average_tracker <port_no> [db_file]\n");
        return -1;
    }
    
    std::cout<<"port no="<<argv[1]<<std::endl;
    std::cout<<"db file="<<argv[2]<<std::endl;
    
    ServerManager::inst()->start(atoi(argv[1]),argv[2]);
    
    return 0;
}
