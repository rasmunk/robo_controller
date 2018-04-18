//
// Created by Rasmus Munk on 18/04/2018.
//

#ifndef ROBO_CONTROLLER_SIMULATIONCLIENT_H
#define ROBO_CONTROLLER_SIMULATIONCLIENT_H

#include <string>
#include <memory>
#include <grpc++/grpc++.h>
#include <messages/simulation.grpc.pb.h>
#include <include/controller/RobotControllerFactory.h>
#include <include/controller/RobotController.h>

class RobotServiceClient
{
private:
    std::shared_ptr<grpc::Channel> _channel;
    std::unique_ptr<network::RobotService::Stub> _stub;
public:
    RobotServiceClient(const std::string server_address);
    bool Add(const RobotController& controller, Controller_type) const;
};


#endif //ROBO_CONTROLLER_SIMULATIONCLIENT_H
