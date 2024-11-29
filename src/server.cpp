#include <grpcpp/grpcpp.h>
#include "math_operations.grpc.pb.h"
#include <cmath>
#include <iostream>

class MathServiceImpl final : public math::MathService::Service {
public:
    grpc::Status Add(grpc::ServerContext* context, const math::MathRequest* request,
        math::MathResponse* response) override {
        response->set_result(request->num1() + request->num2());
        return grpc::Status::OK;
    }

    grpc::Status Subtract(grpc::ServerContext* context, const math::MathRequest* request,
        math::MathResponse* response) override {
        response->set_result(request->num1() - request->num2());
        return grpc::Status::OK;
    }

    grpc::Status Multiply(grpc::ServerContext* context, const math::MathRequest* request,
        math::MathResponse* response) override {
        response->set_result(request->num1() * request->num2());
        return grpc::Status::OK;
    }

    grpc::Status Divide(grpc::ServerContext* context, const math::MathRequest* request,
        math::MathResponse* response) override {
        if (request->num2() == 0) {
            response->set_error("Division by zero is not allowed.");
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Division by zero");
        }
        response->set_result(request->num1() / request->num2());
        return grpc::Status::OK;
    }

    grpc::Status Power(grpc::ServerContext* context, const math::MathRequest* request,
        math::MathResponse* response) override {
        response->set_result(pow(request->num1(), request->num2()));
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