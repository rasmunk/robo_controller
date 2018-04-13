//
// Created by Rasmus Munk on 20/08/2017.
//

#ifndef EMERGENT_CONTROLLER_ROBOTSERVER_H
#define EMERGENT_CONTROLLER_ROBOTSERVER_H

#include <grpc++/grpc++.h>
#include <include/controller/RobotController.h>
#include <simulation.grpc.pb.h>

class SimulationServiceImpl final : public network::Simulation::Service {
public:
    grpc::Status SetGenome(grpc::ServerContext*, const network::Genome*, network::Empty*) override;

    void sink(std::shared_ptr<RobotController>);

private:
    std::shared_ptr<RobotController> _robot_controller;
};

#endif // EMERGENT_CONTROLLER_ROBOTSERVER_H
