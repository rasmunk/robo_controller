//
// Created by Rasmus Munk on 21/08/2017.
//

#ifndef EMERGENT_CONTROLLER_ROBOSERVER_H
#define EMERGENT_CONTROLLER_ROBOSERVER_H

#include <grpc++/grpc++.h>
#include <simulation.grpc.pb.h>
#include <thread>

class RobotServer {
private:
    std::thread _runner;
    std::unique_ptr<grpc::ServerBuilder> _builder;
    std::unique_ptr<grpc::Server> _server;
    std::string _server_address;
    void launch_server();
    void quit();

public:
    RobotServer(const std::string& server_address);
    ~RobotServer() { this->quit(); }
    void register_service(network::Simulation::Service& service);
    void start();
    void stop();

};

#endif //EMERGENT_CONTROLLER_ROBOSERVER_H
