//
// Created by Rasmus Munk on 12/04/2018.
//

#ifndef EMERGENT_CONTROLLER_ROBOTMANAGER_H
#define EMERGENT_CONTROLLER_ROBOTMANAGER_H

#include <vector>
#include <include/controller/RobotController.h>
#include <include/controller/RobotControllerFactory.h>

class RobotManager {
private:
    std::vector<std::pair<std::unique_ptr<RobotController>, Controller_type>> _controllers;

public:
    void add(std::unique_ptr<RobotController> robot_controller, Controller_type);
    void run();
};


#endif //EMERGENT_CONTROLLER_ROBOTMANAGER_H
