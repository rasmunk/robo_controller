//
// Created by Rasmus Munk on 20/08/2017.
//

#ifndef EMERGENT_CONTROLLER_ROBOTSERVER_H
#define EMERGENT_CONTROLLER_ROBOTSERVER_H

#include <grpc++/grpc++.h>
#include <include/controller/RobotController.h>
#include <simulation.grpc.pb.h>
/*
class SimulationServiceImpl final : public network::Simulation::Service {
private:
    std::vector<std::shared_ptr<RobotController>> _controllers;

public:
    grpc::Status SetGenome(grpc::ServerContext*, const network::Genome*, network::Empty*) override;
    void add(std::shared_ptr<RobotController>);
};*/

#endif // EMERGENT_CONTROLLER_ROBOTSERVER_H
