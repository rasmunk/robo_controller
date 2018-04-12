//
// Created by Rasmus Munk on 27/01/2017.
//

#ifndef EMERGENT_ROBOT_ROBOTCONTROLLER_H
#define EMERGENT_ROBOT_ROBOTCONTROLLER_H

#include <include/configuration/RobotConfiguration.h>

class RobotController  {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~RobotController() = default;
};

#endif //EMERGENT_ROBOT_ROBOTCONTROLLER_H
