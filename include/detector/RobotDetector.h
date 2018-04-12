//
// Created by 40161642 on 15/12/2016.
//

#ifndef TEST3_ROBOTDETECTOR_H
#define TEST3_ROBOTDETECTOR_H
#include <include/detector/Detector.h>

class RobotDetector : public Detector {
private:
    std::string reference_image_path;
    cv::Mat reference_mat;
    cv::Ptr<cv::ORB> orb;
    std::vector<cv::KeyPoint>
        kpts1; // Keypoints that describe the object to be found
    cv::Mat desc1; // Descriptor Matrix of the object to be found
    const float inlier_threshold = 4.0f; // Distance threshold to identify inliers of a detected match
    const float nn_match_ratio = 0.70f; // Nearest neighbor matching ratio for
    void initialize();

public:
    RobotDetector(){};
    void initialize(std::string) override;
    bool find(const cv::Mat&) override;
};

#endif // TEST3_ROBOTDETECTOR_H
