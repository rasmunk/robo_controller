//
// Created by Rasmus Munk on 04/02/2017.
//

#ifndef EMERGENT_ROBOT_SHAREDFRAME_H
#define EMERGENT_ROBOT_SHAREDFRAME_H

#include "FrameStructure.h"
#include <mutex>

class SharedFrame : public FrameStructure {
private:
    cv::Mat _mat;
    std::mutex _mutex;

public:
    virtual void add(cv::Mat&&) override;
    virtual size_t size() override;
    virtual cv::Mat pop() override;
};

#endif // EMERGENT_ROBOT_SHAREDFRAME_H
