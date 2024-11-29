#include <grpcpp/grpcpp.h>
#include "math_operations.grpc.pb.h"
#include <iostream>
#include <future>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using math::MathService;
using math::MathRequest;
using math::MathResponse;

class MathClient {
public:
    MathClient(std::shared_ptr<Channel> channel)
        : stub_(MathService::NewStub(channel)) {
    }

    void Add(double num1, double num2) {
        MathRequest request;
        request.set_num1(num1);
        request.set_num2(num2);

        MathResponse response;
        ClientContext context;

        Status status = stub_->Add(&context, request, &response);
        if (status.ok()) {
            std::cout << "Addition result: " << response.result() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Subtract(double num1, double num2) {
        MathRequest request;
        request.set_num1(num1);
        request.set_num2(num2);

        MathResponse response;
        ClientContext context;

        Status status = stub_->Subtract(&context, request, &response);
        if (status.ok()) {
            std::cout << "Subtraction result: " << response.result() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Multiply(double num1, double num2) {
        MathRequest request;
        request.set_num1(num1);
        request.set_num2(num2);

        MathResponse response;
        ClientContext context;

        Status status = stub_->Multiply(&context, request, &response);
        if (status.ok()) {
            std::cout << "Multiplication result: " << response.result() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Divide(double num1, double num2) {
        MathRequest request;
        request.set_num1(num1);
        request.set_num2(num2);

        MathResponse response;
        ClientContext context;

        Status status = stub_->Divide(&context, request, &response);
        if (status.ok()) {
            std::cout << "Division result: " << response.result() << std::endl;
        }
        else {
            std::cout << "Error: " << status.error_message() << std::endl;
        }
    }


    void Power(double num1, double num2) {
        MathRequest request;
        request.set_num1(num1);
        request.set_num2(num2);

        MathResponse response;
        ClientContext context;

        Status status = stub_->Power(&context, request, &response);
        if (status.ok()) {
            std::cout << "Power result: " << response.result() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    std::future<void> MultiplyAsync(double num1, double num2) {
        return std::async(std::launch::async, [this, num1, num2]() {
            MathRequest request;
            request.set_num1(num1);
            request.set_num2(num2);

            MathResponse response;
            ClientContext context;

            Status status = stub_->Multiply(&context, request, &response);
            if (status.ok()) {
                std::cout << "Multiplication result (async): " << response.result() << std::endl;
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