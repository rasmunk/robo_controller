//
// Created by 40161642 on 15/12/2016.
//

#ifndef TEST3_DETECTOR_H
#define TEST3_DETECTOR_H
#include <opencv2/opencv.hpp>

class Detector {
public:
    virtual void initialize(std::string) = 0;
    virtual bool find(const cv::Mat&) = 0;
    virtual ~Detector() = default;
};

#endif // TEST3_DETECTOR_H
