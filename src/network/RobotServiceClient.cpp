//
// Created by Rasmus Munk on 18/04/2018.
//


#include <messages/simulation.grpc.pb.h>
#include <include/network/RobotServiceClient.h>
#include <memory>
#include <include/network/RobotServiceImpl.h>

using namespace std;
using namespace grpc;
using namespace network;

RobotServiceClient::RobotServiceClient(const std::string server_address) :
        _channel(CreateChannel(server_address, InsecureChannelCredentials())), _stub
        (network::RobotService::NewStub(_channel)) {};



bool RobotServiceClient::Add(const RobotController &controller,
                             Controller_type controller_type) const {
    // message
    Robot robot;
    robot.set_id(controller.id);
    robot.set_type((Robot::Controller_type)controller_type);

    // server response
    Response response;
    ClientContext clientContext;

    Status status = _stub->Add(&clientContext, robot, &response);

    if (status.ok()) {
        return response.status() == 0;
    }
    return false;
}