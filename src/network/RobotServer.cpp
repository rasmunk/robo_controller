//
// Created by Rasmus Munk on 21/08/2017.
//

#include <include/network/RobotServer.h>
#include <time.h>

using grpc::InsecureServerCredentials;
using grpc::ServerBuilder;
using namespace std;

RobotServer::RobotServer(const string& server_address, grpc::Service& service)
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
    _builder->RegisterService(&service);
    _runner = thread(&RobotServer::launch_server, this);
}

// TODO -> state machine of incomming messages
// TODO -> queue to forward messages to listener
void RobotServer::launch_server()
{
    _server = _builder->BuildAndStart();
    cout << "Server listening on " << _server_address << endl;
    _server->Wait();
}

void RobotServer::stop()
{
    cout << "Shutting down" << endl;
    _server->Shutdown();
    if (_runner.joinable()) {
        _runner.join();
    }
}