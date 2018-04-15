//
// Created by 40161642 on 15/12/2016.
//

#ifndef TEST3_DETECTORFACTORY_H
#define TEST3_DETECTORFACTORY_H
#include <include/detector/Detector.h>
#include <memory>

enum Detector_type { Robot };
class DetectorFactory {
public:
    std::unique_ptr<Detector> make_detector(Detector_type);
};

#endif // TEST3_DETECTORFACTORY_H
