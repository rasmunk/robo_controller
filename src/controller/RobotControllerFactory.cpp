//
// Created by Rasmus Munk on 27/01/2017.
//
#include <include/controller/RobotControllerFactory.h>
#include <include/controller/ThymioController.h>
#include <include/controller/ThymioEmergentController.h>

using namespace std;

unique_ptr<RobotController> RobotControllerFactory::make_unique_robot_controller(Controller_type controller_type) {
    unique_ptr<RobotController> robot_controller;
    switch (controller_type) {
        case Thymio:
            robot_controller = make_unique<ThymioController>();
            break;
        case Emergent:
            robot_controller = make_unique<ThymioEmergentController>(17, 9, 2);
            break;
        default:
            cerr << "No unique robot controller specified" << endl;
            break;
    }
    return robot_controller;
}

shared_ptr<RobotController> RobotControllerFactory::make_shared_robot_controller(Controller_type controller_type) {
    shared_ptr<RobotController> robot_controller;
    switch (controller_type) {
        case Thymio:
            robot_controller = make_shared<ThymioController>();
            break;
        case Emergent:
            robot_controller = make_shared<ThymioEmergentController>(8, 0, 2);
            break;
        default:
            cerr << "No shared robot controller specified" << endl;
    }
    return robot_controller;
}