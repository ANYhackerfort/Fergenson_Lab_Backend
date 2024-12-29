#include "message.grpc.pb.h"
#include "process_image.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <cstdlib>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>

// Namespace declarations
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

// gRPC Service Implementation
class MessageServiceImpl final : public MessageService::Service {
public:
  grpc::Status SendMessage(grpc::ServerContext *context,
                           const MessageRequest *request,
                           MessageResponse *reply) override {
    std::string receivedMessage = request->message();
    std::cout << "gRPC received message: " << receivedMessage << std::endl;

    // Respond to the gRPC client
    reply->set_response("Server received: " + receivedMessage);
    return grpc::Status::OK;
  }
};

// Function to run the gRPC server
void RunGrpcServer() {
  std::string serverAddress("0.0.0.0:50051");
  MessageServiceImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "gRPC server listening on " << serverAddress << std::endl;

  server->Wait();
}

// WebSocket session function
void do_session(tcp::socket socket) {
  try {
    websocket::stream<tcp::socket> ws(std::move(socket));
    ws.accept(); // Accept the WebSocket handshake

    std::cout << "WebSocket connection established" << std::endl;

    for (;;) {
      // Buffer for incoming messages
      boost::beast::flat_buffer buffer;

      // Read a message from the WebSocket
      ws.read(buffer);
      std::string receivedMessage =
          boost::beast::buffers_to_string(buffer.data());

      // Log the received message
      std::cout << "WebSocket received message: " << receivedMessage
                << std::endl;

      // Respond to the client
      std::string response = "Server received: " + receivedMessage;
      ws.write(asio::buffer(response));
    }
  } catch (const std::exception &e) {
    // General exception handling
    std::cout << "WebSocket Error: " << e.what() << std::endl;
  }
}

int main() {
  try {
    // Start gRPC server in a separate thread
    std::thread grpcThread(RunGrpcServer);

    // Start WebSocket server
    asio::io_context ioc;
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

    std::cout << "WebSocket server listening on port 8080..." << std::endl;

    while (true) {
      tcp::socket socket(ioc);
      acceptor.accept(socket); // Wait for a client to connect

      std::thread(&do_session, std::move(socket)).detach();
    }

    grpcThread.join(); // Ensure the gRPC thread runs indefinitely
  } catch (const std::exception &e) {
    std::cout << "Server Error: " << e.what() << std::endl;
  }
}
