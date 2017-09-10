//
// Created by Rasmus Munk on 20/08/2017.
//

#include <include/network/SimulationServiceImpl.h>
#include <cmake-build-debug/proto-src/simulation.pb.h>

using grpc::ServerContext;
using grpc::ClientContext;
using grpc::Status;
using network::Genome;

Status SimulationServiceImpl::SetGenome(ServerContext* context, const network::Genome* genome,
                                              network::Empty* response) {

    /*auto configuration = _robot_controller->get_configuration_of_type(Emergent);

    configuration->set_genome(genome);

    _robot_controller->update_configuration(configuration);*/
    std::cout << "Received request" << std::endl;

    return Status::OK;
}

void SimulationServiceImpl::sink(std::shared_ptr<RobotController> robot_controller) {
    _robot_controller = robot_controller;
}