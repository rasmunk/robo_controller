//
// Created by 40161642 on 15/12/2016.
//
#include <include/detector/DetectorFactory.h>
#include <include/detector/RobotDetector.h>

using namespace std;
unique_ptr<Detector> DetectorFactory::make_detector(Detector_type detector_type) {
    unique_ptr<Detector> detector;
    if (detector_type == Robot)
    {
        detector = make_unique<RobotDetector>();
    }
    return detector;
}