#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include "process_image.h"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;

void do_session(tcp::socket socket) { 
    try {
        websocket::stream<tcp::socket> ws(std::move(socket));
        ws.accept();  // Accept the WebSocket handshake

        // Path to the image (can be hard-coded or dynamically set)
        std::string imagePath = "/Users/miladhaghighi/Downloads/Screenshot_2024-11-06_at_10.23.53_PM.png";

        // Initialize ImageProcessor with the image path
        ImageProcessor processor(imagePath);

        // Load the image
        if (!processor.loadImage()) {
            std::cerr << "Failed to load image" << std::endl;
            return;
        }

        // Convert to grayscale and detect edges
        processor.convertToGrayscale();
        processor.detectEdges();
        processor.detectMinMax();

        // Get the processed image (edges) as a cv::Mat
        cv::Mat processedImage = processor.getEdges();

        // Save the processed image to a file
        cv::imwrite("/Users/miladhaghighi/Downloads/processed_edges.png", processedImage);

        // Send a simple confirmation message to the frontend
        ws.write(asio::buffer("Image processing and edge detection completed"));

        std::cout << "Processed image saved to file, and confirmation message sent to the client." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        asio::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "WebSocket server listening on port 8080..." << std::endl;

        for (;;) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);  // Wait for a client to connect
            std::thread(&do_session, std::move(socket)).detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Server Error: " << e.what() << std::endl;
    }
}
