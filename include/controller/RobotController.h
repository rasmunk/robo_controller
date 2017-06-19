//
// Created by Rasmus Munk on 27/01/2017.
//

#ifndef EMERGENT_ROBOT_ROBOTCONTROLLER_H
#define EMERGENT_ROBOT_ROBOTCONTROLLER_H
#include <include/detector/Detector.h>
#include <memory>

class RobotController {

public:
    virtual void start() = 0;
    virtual void stop() = 0;
    //virtual void set_shared_detector(std::shared_ptr<Detector>) = 0;

};

#endif //EMERGENT_ROBOT_ROBOTCONTROLLER_H
