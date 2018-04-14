//
// Created by Rasmus Munk on 20/08/2017.
//

#include <include/network/SimulationServiceImpl.h>

using grpc::ClientContext;
using grpc::ServerContext;
using grpc::Status;
using network::Genome;
/*
Status SimulationServiceImpl::SetGenome(
    ServerContext* context, const network::Genome* genome, network::Empty* response)
{
    /*auto configuration =
_robot_controller->get_configuration_of_type(Emergent);

configuration->set_genome(genome);

_robot_controller->update_configuration(configuration);
    std::cout << "Received request" << std::endl;

    return Status::OK;
}

void SimulationServiceImpl::add(std::shared_ptr<RobotController> robot_controller)
{
    _controllers.push_back(robot_controller);
}*/