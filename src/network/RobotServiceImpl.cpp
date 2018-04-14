//
// Created by Rasmus Munk on 14/04/2018.
//

#include "include/network/RobotServiceImpl.h"
#include <include/controller/RobotControllerFactory.h>

::grpc::Status RobotServiceImpl::Add(::grpc::ServerContext *context,
                                     const ::network::Robot *request,
                                     ::network::Response *response) {

    Controller_type controller_type = ThymioObstacleAvoidance;
    RobotControllerFactory robotControllerFactory;
    RobotConfig robot_config;
    robot_config.set("ip", "127.0.0.1");
    robot_config.set("port", "33333");
    robot_config.set("aesl_file", "../res/config/OAThymio.aesl");

    auto robot_controller = robotControllerFactory.make_shared_robot_controller(
            ThymioObstacleAvoidance, robot_config);
    robot_controller->id = request->id();
    _robot_manager->run_controller(robot_controller, controller_type);

    response->set_status(0);
    return grpc::Status::OK;
}