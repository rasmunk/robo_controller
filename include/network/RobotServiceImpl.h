//
// Created by Rasmus Munk on 14/04/2018.
//

#ifndef EMERGENT_CONTROLLER_ROBOTSERVICEIMPL_H
#define EMERGENT_CONTROLLER_ROBOTSERVICEIMPL_H

#include <messages/simulation.grpc.pb.h>
#include <include/manager/RobotManager.h>

class RobotServiceImpl final : public network::RobotService::Service
{
private:
    // Shared active controllers
    std::shared_ptr<RobotManager> _robot_manager;
    // Simulator client
    std::unique_ptr<RobotServiceClient> _robot_service_client;

public:
    RobotServiceImpl(std::shared_ptr<RobotManager> robot_manager,
                     std::unique_ptr<RobotServiceClient> robot_service_client) :
            _robot_manager(move(robot_manager)), _robot_service_client(move(robot_service_client)) {};

    grpc::Status Add(grpc::ServerContext *, const network::Robot *, network::Response *) override;
    /* grpc::Status Remove(grpc::ServerContext*, const network::Robot*, network::Response*) override;
     grpc::Status Get(grpc::ServerContext*, const network::Robot*, network::Response*) override;
     grpc::Status Update(grpc::ServerContext*, const network::Robot*, network::Response*) override;*/
};


#endif //EMERGENT_CONTROLLER_ROBOTSERVICEIMPL_H
