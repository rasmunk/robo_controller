//
// Created by Rasmus Munk on 27/01/2017.
//
#include <include/controller/RobotControllerFactory.h>
#include <include/controller/ThymioController.h>
//#include <include/controller/ThymioEmergentController.h>
#include <include/controller/ThymioOAController.h>

using namespace std;

unique_ptr<RobotController> RobotControllerFactory::make_unique_robot_controller(
    Controller_type controller_type, const RobotConfig& robot_config)
{
    unique_ptr<RobotController> robot_controller;
    switch (controller_type) {
    case ThymioBasic:
        robot_controller = make_unique<ThymioController>(robot_config);
        break;
    case ThymioEmergent:
        // robot_controller = make_unique<ThymioEmergentController>();
        break;
    case ThymioObstacleAvoidance:
        robot_controller = make_unique<ThymioOAController>(robot_config);
        break;
    default:
        cerr << "No unique robot controller specified" << endl;
        break;
    }
    return robot_controller;
}

shared_ptr<RobotController> RobotControllerFactory::make_shared_robot_controller(
    Controller_type controller_type, const RobotConfig& robot_config)
{
    shared_ptr<RobotController> robot_controller;
    switch (controller_type) {
    case ThymioBasic:
        robot_controller = make_shared<ThymioController>(robot_config);
        break;
    case ThymioEmergent:
        // robot_controller = make_shared<ThymioEmergentController>();
        break;
    case ThymioObstacleAvoidance:
        robot_controller = make_shared<ThymioOAController>(robot_config);
        break;
    default:
        cerr << "No shared robot controller specified" << endl;
        break;
    }
    return robot_controller;
}