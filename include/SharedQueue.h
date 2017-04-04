//
// Created by 40161642 on 14/12/2016.
//

#ifndef TEST4_SHAREDQUEUE_H
#define TEST4_SHAREDQUEUE_H
#include <include/FrameStructure.h>
#include <queue>
#include <mutex>

class SharedQueue : public FrameStructure
{
private:
    std::queue<cv::Mat> _queue;
    std::mutex _mutex;
public:
    virtual void add(cv::Mat&&) override ;
    virtual size_t size() override ;
    virtual cv::Mat pop() override ;
};

#endif //TEST4_SHAREDQUEUE_H
