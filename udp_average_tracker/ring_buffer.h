//
//  ring_buffer.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef udp_average_tracker_ring_buffer_h
#define udp_average_tracker_ring_buffer_h

#include <vector>
#include <atomic>
#include <chrono>
#include "producer_consumer.h"

template <class T>
class RingBuffer:public ProducerConsumer<T>
{
public:
    RingBuffer(size_t capacity)
        :_capacity(capacity),
        _produce_count(0),
        _consume_count(0)
    {
        _buffer.resize(_capacity);
    }
    
    virtual ~RingBuffer() {}
    
    void enqueue(T data)
    {
        while(size()+1 >= _capacity)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        _buffer[_produce_count] = data;
        _produce_count = (_produce_count+1)%_capacity;
    }
    
    T dequeue()
    {
        while(size()<=0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        T data = _buffer[_consume_count];
        _consume_count = (_consume_count+1)%_capacity;
        return data;
    }
    
private:
    bool isAvailabe()
    {
        if(_produce_count >= _consume_count)
        {
            return (_produce_count-_consume_count)>0;
        }
        
        return ((_produce_count+_capacity)-_consume_count)>0;
    }

    size_t size()
    {
        if(_produce_count >= _consume_count)
        {
            return (_produce_count-_consume_count);
        }
        
        return ((_produce_count+_capacity)-_consume_count);
    }
    
    size_t _capacity;
    std::vector<T> _buffer;
    std::atomic_size_t _produce_count,_consume_count;
};

#endif
