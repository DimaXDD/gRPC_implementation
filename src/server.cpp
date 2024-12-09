#include <grpcpp/grpcpp.h>
#include "math_operations.grpc.pb.h"
#include <cmath>
#include <iostream>

class MathServiceImpl final : public math::MathService::Service {
public:
    grpc::Status Add(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(request->x() + request->y());
        return grpc::Status::OK;
    }

    grpc::Status Sub(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(request->x() - request->y());
        return grpc::Status::OK;
    }

    grpc::Status Mul(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(request->x() * request->y());
        return grpc::Status::OK;
    }

    grpc::Status Div(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        if (request->y() == 0) {
            response->set_error("Division by zero is not allowed.");
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Division by zero");
        }
        response->set_z(request->x() / request->y());
        return grpc::Status::OK;
    }

    grpc::Status Pow(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(pow(request->x(), request->y()));
        return grpc::Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    MathServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main() {
    RunServer();
    return 0;
}