//
// Created by Rasmus Munk on 15/04/2018.
//

#include <include/network/GrpcServer.h>

using namespace std;
using namespace grpc;

GrpcServer::GrpcServer(const std::string& server_address, grpc::Service& service)
    : _builder(make_unique<ServerBuilder>())
{
    if (_builder == nullptr) {
        throw runtime_error("Failed to intialize the grpc ServerBuilder");
    }
    if (server_address == "") {
        throw runtime_error("server_address can't be blank");
    }
    _builder->AddListeningPort(server_address, InsecureServerCredentials());
    _builder->RegisterService(&service);
    _runner = thread(&GrpcServer::launch_server, this);
}


void GrpcServer::launch_server() {
    _server = _builder->BuildAndStart();
    _server->Wait();
}

void GrpcServer::stop() {
    _server->Shutdown();
    if (_runner.joinable()) {
        _runner.join();
    }
}