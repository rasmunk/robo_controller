//
// Created by Rasmus Munk on 12/04/2018.
//

#ifndef EMERGENT_CONTROLLER_ROBOTMANAGER_H
#define EMERGENT_CONTROLLER_ROBOTMANAGER_H

#include <vector>
#include <QCoreApplication>
#include <include/controller/RobotController.h>
#include <include/controller/RobotControllerFactory.h>

class RobotManager {
private:
    std::unique_ptr<QCoreApplication> _qcore_application;
    std::vector<std::pair<std::shared_ptr<RobotController>, Controller_type>>
        _controllers;

public:
    void add(std::shared_ptr<RobotController> robot_controller, Controller_type);
    void run();
};

#endif // EMERGENT_CONTROLLER_ROBOTMANAGER_H
