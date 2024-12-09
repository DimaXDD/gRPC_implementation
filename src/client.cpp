#include <grpcpp/grpcpp.h>
#include "math_operations.grpc.pb.h"
#include <iostream>
#include <future>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using math::MathService;
using math::Parm2Request;
using math::Parm2Result;

class MathClient {
public:
    MathClient(std::shared_ptr<Channel> channel)
        : stub_(MathService::NewStub(channel)) {
    }

    void Add(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Add(&context, request, &response);
        if (status.ok()) {
            std::cout << "Addition result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Subtract(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Sub(&context, request, &response);
        if (status.ok()) {
            std::cout << "Subtraction result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Multiply(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Mul(&context, request, &response);
        if (status.ok()) {
            std::cout << "Multiplication result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Divide(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Div(&context, request, &response);
        if (status.ok()) {
            std::cout << "Division result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << status.error_message() << std::endl;
        }
    }


    void Power(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Pow(&context, request, &response);
        if (status.ok()) {
            std::cout << "Power result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    std::future<void> MultiplyAsync(double x, double y) {
        return std::async(std::launch::async, [this, x, y]() {
            Parm2Request request;
            request.set_x(x);
            request.set_y(y);

            Parm2Result response;
            ClientContext context;

            Status status = stub_->Mul(&context, request, &response);
            if (status.ok()) {
                std::cout << "Multiplication result (async): " << response.z() << std::endl;
            }
            else {
                std::cout << "Error: " << response.error() << std::endl;
            }
            });
    }

private:
    std::unique_ptr<MathService::Stub> stub_;
};

int main() {
    MathClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    client.Add(3, 4);
    client.Subtract(10, 5);
    client.Multiply(6, 7);
    auto multiplyFuture = client.MultiplyAsync(6, 7);
    multiplyFuture.get();
    client.Divide(10, 2);
    client.Divide(10, 0);
    client.Power(2, 3);

    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}