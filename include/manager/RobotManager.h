//
// Created by Rasmus Munk on 12/04/2018.
//

#ifndef EMERGENT_CONTROLLER_ROBOTMANAGER_H
#define EMERGENT_CONTROLLER_ROBOTMANAGER_H

#include <vector>
#include <include/controller/RobotController.h>
#include <include/controller/RobotControllerFactory.h>

class RobotManager {

    std::vector<RobotController> _controllers;

public:
    void add(const RobotController&, Controller_type);
};


#endif //EMERGENT_CONTROLLER_ROBOTMANAGER_H
