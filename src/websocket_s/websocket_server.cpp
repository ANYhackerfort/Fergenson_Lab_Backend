#include "message.grpc.pb.h"
#include "openCV_f/process_image.h"
#include "stateOfLab_s/state_of_lab.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <cstdlib>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>

// Namespace declarations
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;
using json = nlohmann::json;

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
  std::string serverAddress("192.168.2.136:50053");
  MessageServiceImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  if (server) {
    std::cout << "gRPC server listening on " << serverAddress << std::endl;
  } else {
    std::cerr << "Failed to start gRPC server!" << std::endl;
    return;
  }

  server->Wait();
}

// WebSocket session function
void do_session(tcp::socket socket) {
  try {
    websocket::stream<tcp::socket> ws(std::move(socket));
    ws.accept();
    std::cout << "WebSocket connection established" << std::endl;

    for (;;) {
      boost::beast::flat_buffer buffer;

      // Read WebSocket message
      ws.read(buffer);
      std::string receivedMessage =
          boost::beast::buffers_to_string(buffer.data());

      std::cout << "WebSocket received message: " << receivedMessage
                << std::endl;

      // Parse the received JSON message
      json request;
      try {
        request = json::parse(receivedMessage);
      } catch (const json::exception &e) {
        std::string errorResponse =
            R"({"type":"error","payload":{"message":"Invalid JSON format"}})";
        ws.write(asio::buffer(errorResponse));
        continue;
      }

      // Extract type and payload
      std::string type = request.value("type", "");
      json payload = request.value("payload", json::object());

      // Prepare a response JSON
      json response;

      if (type == "get_component_angle") {
        // Handle "get_component_angle" request
        std::string id = payload.value("id", "");
        double angle = 45.0; // Replace with actual logic to fetch the angle

        response = {{"type", "circular_thermometer_angle"},
                    {"payload", {{"id", id}, {"angle", angle}}}};
      } else {
        // Handle unknown request types
        response = {{"type", "error"},
                    {"payload", {{"message", "Unknown request type"}}}};
      }

      // Send response back to the client
      ws.write(asio::buffer(response.dump()));
    }
  } catch (const std::exception &e) {
    // Handle exceptions gracefully
    std::cout << "WebSocket Error: " << e.what() << std::endl;
  }
}

int main() {
  try {
    // Create all labs here
    auto labs = std::make_shared<StateOfLabs>("frankhertz1");

    // Start WebSocket server
    asio::io_context ioc;
    tcp::acceptor acceptor(ioc,
                           tcp::endpoint(asio::ip::address_v4::any(), 8080));

    std::cout << "WebSocket server listening on port 8080..." << std::endl;

    while (true) {
      tcp::socket socket(ioc);
      acceptor.accept(socket); // Wait for a client to connect

      // Pass the socket and shared labs instance to the session thread
      std::thread(&do_session, std::move(socket), labs).detach();
    }
  } catch (const std::exception &e) {
    std::cout << "Server Error: " << e.what() << std::endl;
  }
}
