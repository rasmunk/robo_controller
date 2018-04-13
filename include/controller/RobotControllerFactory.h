//
// Created by Rasmus Munk on 27/01/2017.
//
#ifndef EMERGENT_ROBOT_ROBOTCONTROLLERFACTORY_H
#define EMERGENT_ROBOT_ROBOTCONTROLLERFACTORY_H

#include <include/controller/RobotController.h>
#include <memory>

enum Controller_type { ThymioBasic, ThymioEmergent, ThymioObstacleAvoidance };

class RobotControllerFactory {
public:
    std::unique_ptr<RobotController> make_unique_robot_controller(
        Controller_type, const RobotConfig& robot_config);
    std::shared_ptr<RobotController> make_shared_robot_controller(
        Controller_type, const RobotConfig& robot_config);
};

#endif // EMERGENT_ROBOT_ROBOTCONTROLLERFACTORY_H
