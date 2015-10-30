//
//  TimeValue.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef udp_average_tracker_TimeValue_h
#define udp_average_tracker_TimeValue_h
#include <time.h>


struct TimeValue
{
    unsigned int _value;
    time_t _timestamp;
};

#endif
