//
// Created by Rasmus Munk on 21/08/2017.
//

#include <include/network/RobotServer.h>

using grpc::InsecureServerCredentials;
using grpc::ServerBuilder;
using namespace std;

RobotServer::RobotServer(const string& server_address)
    : _server_address(server_address)
    , _builder(make_unique<ServerBuilder>())
{
    if (_builder == nullptr) {
        throw runtime_error{ "Failed to initialize the grpc ServerBuilder" };
    }
    // TODO -> improve server_address initialization condition
    if (_server_address == "") {
        throw runtime_error{ "server address can't be blank" };
    }
    _builder->AddListeningPort(_server_address, InsecureServerCredentials());
}

void RobotServer::register_service(network::Simulation::Service& service)
{
    _builder->RegisterService(&service);
}

void RobotServer::launch_server()
{
    _server = _builder->BuildAndStart();
    cout << "Server listening on " << _server_address << endl;
    _server->Wait();
}

void RobotServer::start()
{
    _runner = thread(&RobotServer::launch_server, this);
}

void RobotServer::stop()
{
    cout << "Shutting down" << endl;
    _server->Shutdown();
}

void RobotServer::quit()
{
    this->stop();
    if (_runner.joinable()) {
        _runner.join();
    }
}