//
// Created by 40161642 on 15/12/2016.
//

#ifndef TEST3_FRAMESTRUCTURE_H
#define TEST3_FRAMESTRUCTURE_H
#include <opencv2/opencv.hpp>
class FrameStructure {
public:
    virtual void add(cv::Mat&&) = 0;
    virtual size_t size() = 0;
    virtual cv::Mat pop() = 0;
    virtual ~FrameStructure() = default;
};

#endif // TEST3_FRAMESTRUCTURE_H
