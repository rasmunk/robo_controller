//
// Created by Rasmus Munk on 15/04/2018.
//

#ifndef PLAYGROUND_GRPCSERVER_H
#define PLAYGROUND_GRPCSERVER_H

#include <thread>
#include <memory>
#include <grpc++/grpc++.h>

class GrpcServer
{
private:
    std::thread _runner;
    std::unique_ptr<grpc::ServerBuilder> _builder;
    std::unique_ptr<grpc::Server> _server;
    void launch_server();
    void stop();

public:
    GrpcServer(const std::string& server_address, grpc::Service&);
    ~GrpcServer() { this->stop(); }
};


#endif //PLAYGROUND_GRPCSERVER_H
