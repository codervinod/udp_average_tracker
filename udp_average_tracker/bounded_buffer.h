//
//  bounded_buffer.h
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/30/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef __udp_average_tracker__bounded_buffer__
#define __udp_average_tracker__bounded_buffer__

#include <stdio.h>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "producer_consumer.h"

template <class T>
class BoundedBuffer:public ProducerConsumer<T>
{
public:
    BoundedBuffer(size_t capacity)
    :_capacity(capacity)
    {
        
    }
    
    virtual ~BoundedBuffer()
    {
        
    }
    
    void enqueue(T data)
    {
        std::unique_lock<std::mutex> lk(_q_mutex);
        while(_q.size() > _capacity)
        {
            _full_cv.wait(lk);
        }
        
        _q.push(data);
        
        if(_q.size()==1)
        {
            _empty_cv.notify_one();
        }
    }
    
    T dequeue()
    {
        std::unique_lock<std::mutex> lk(_q_mutex);
        while(_q.empty())
        {
            _empty_cv.wait(lk);
        }
        
        T data = _q.front();
        _q.pop();
        
        if(_q.size() + 1 >= _capacity)
        {
            _full_cv.notify_one();
        }
        return data;
    }
    
private:
    std::queue<T> _q;
    std::mutex _q_mutex;
    std::condition_variable _full_cv,_empty_cv;
    size_t _capacity;
};

#endif /* defined(__udp_average_tracker__bounded_buffer__) */
