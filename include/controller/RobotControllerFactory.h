//
// Created by Rasmus Munk on 27/01/2017.
//
#ifndef EMERGENT_ROBOT_ROBOTCONTROLLERFACTORY_H
#define EMERGENT_ROBOT_ROBOTCONTROLLERFACTORY_H
#include <memory>
#include <include/controller/RobotController.h>

enum Controller_type {ThymioBasic, ThymioEmergent, ThymioObstacleAvoidance};
class RobotControllerFactory {
public:
    std::unique_ptr<RobotController> make_unique_robot_controller(Controller_type);
    std::shared_ptr<RobotController> make_shared_robot_controller(Controller_type);
};


#endif //EMERGENT_ROBOT_ROBOTCONTROLLERFACTORY_H
