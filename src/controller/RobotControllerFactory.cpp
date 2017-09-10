//
// Created by Rasmus Munk on 27/01/2017.
//
#include <include/controller/RobotControllerFactory.h>
#include <include/controller/ThymioController.h>
#include <include/controller/ThymioEmergentController.h>
#include <include/controller/ThymioOAController.h>

using namespace std;

unique_ptr<RobotController> RobotControllerFactory::make_unique_robot_controller(Controller_type controller_type) {
    unique_ptr<RobotController> robot_controller;
    switch (controller_type) {
        case ThymioBasic:
            robot_controller = make_unique<ThymioController>();
            break;
        case ThymioEmergent:
            robot_controller = make_unique<ThymioEmergentController>();
            break;
        case ThymioObstacleAvoidance:
            robot_controller = make_unique<ThymioOAController>();
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
        case ThymioBasic:
            robot_controller = make_shared<ThymioController>();
            break;
        case ThymioEmergent:
            robot_controller = make_shared<ThymioEmergentController>();
            break;
        case ThymioObstacleAvoidance:
            robot_controller = make_shared<ThymioOAController>();
            break;
        default:
            cerr << "No shared robot controller specified" << endl;
            break;
    }
    return robot_controller;
}