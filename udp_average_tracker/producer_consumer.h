//
//  producer_consumer.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef udp_average_tracker_producer_consumer_h
#define udp_average_tracker_producer_consumer_h

template <class T>
class ProducerConsumer
{
public:
    ProducerConsumer(){}
    
    virtual ~ProducerConsumer() {}
    virtual void enqueue(T data)=0;
    virtual T dequeue()=0;
protected:
};
#endif
