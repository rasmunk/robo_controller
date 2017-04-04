//
// Created by Rasmus Munk on 27/01/2017.
//

#include "include/controller/RobotControllerFactory.h"
#include "include/controller/ThymioController.h"
using namespace std;

unique_ptr<RobotController> RobotControllerFactory::make_unique_robot_controller(Controller_type controller_type) {
    unique_ptr<RobotController> robot_controller;
    if (controller_type == Thymio) {
        robot_controller = make_unique<ThymioController>();
    }
    return robot_controller;
}

shared_ptr<RobotController> RobotControllerFactory::make_shared_robot_controller(Controller_type controller_type) {
    shared_ptr<RobotController> robot_controller;
    if (controller_type == Thymio) {
        robot_controller = make_shared<ThymioController>();
    }
    return robot_controller;
}