//
// Created by Rasmus Munk on 21/08/2017.
//

#include <include/network/RobotServer.h>
#include <time.h>

using grpc::InsecureServerCredentials;
using grpc::ServerBuilder;
using namespace std;

RobotServer::RobotServer(const string& server_address, grpc::Service& service)
    : _builder(make_unique<ServerBuilder>())
{
    if (_builder == nullptr) {
        throw runtime_error{ "Failed to initialize the grpc ServerBuilder" };
    }
    // TODO -> improve server_address initialization condition
    if (server_address == "") {
        throw runtime_error{ "server address can't be blank" };
    }
    _builder->AddListeningPort(server_address, InsecureServerCredentials());
    _builder->RegisterService(&service);
    _runner = thread(&RobotServer::launch_server, this);
}

// TODO -> state machine of incomming messages
// TODO -> queue to forward messages to listener
void RobotServer::launch_server()
{
    _server = _builder->BuildAndStart();
    _server->Wait();
}

void RobotServer::stop()
{
    _server->Shutdown();
    if (_runner.joinable()) {
        _runner.join();
    }
}