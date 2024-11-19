#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif 

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "process_image.h"
#include "liboai.h"

// Namespace declarations
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

// Function to test PyTorch integration
//void testPyTorch() {
//    // Create a 3x3 random tensor
//    torch::Tensor tensor = torch::rand({3, 3});
//    std::cout << "Testing PyTorch Installation:" << std::endl;
//    std::cout << "Random Tensor:\n" << tensor << std::endl;
//
//    // Perform a simple operation
//    tensor = tensor * 2;
//    std::cout << "Tensor after multiplication:\n" << tensor << std::endl;
//}

void do_session(tcp::socket socket) { 
    try {
        websocket::stream<tcp::socket> ws(std::move(socket));
        ws.accept();  // Accept the WebSocket handshake
        //Path to the image (can be hard-coded or dynamically set)
        std::string imagePath = "/Users/matthewzhang/Downloads/file.png";

        // Initialize ImageProcessor with the image path
        ImageProcessor processor(imagePath);

        // Load the image
        if (!processor.loadImage()) {
            std::cerr << "Failed to load image" << std::endl;
            return;
        }

        // Preprocess the image for OCR
        processor.preprocessForOCR();
        cv::Mat gaussian_image = processor.getPreproccessed_ocr();

        // Save the processed image to a file
        std::string savePath = "/Users/matthewzhang/websocket-Fergenson/test_data/processed_image.png";
        if (!cv::imwrite(savePath, gaussian_image)) {
            ws.write(asio::buffer("Failed to save processed image"));
            std::cerr << "Failed to save processed image to " << savePath << std::endl;
            return;
        }

        // Test PyTorch functionality
        //testPyTorch();

        // Send a confirmation message to the frontend
        ws.write(asio::buffer("Image processing and edge detection completed"));

        std::cout << "Processed image saved to file, and confirmation message sent to the client." << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void reply(tcp::socket socket)
{
    try {
        websocket::stream<tcp::socket> ws(std::move(socket));
        ws.accept();  // Accept the WebSocket handshake

        liboai::OpenAI open_ai;
        liboai::Conversation chat_box;

        chat_box.SetSystemData("You are a professional physics chatbox");

        boost::beast::multi_buffer buffer;
        if (open_ai.auth.SetKeyEnv("OPENAI"))
        {
            std::cout << "Did this even work" << '\n';
            try 
            {
                while (true) 
                {
                    ws.read(buffer);  // Blocking read
                    std::string chat_message = boost::beast::buffers_to_string(buffer.data());
                    std::cout << "Received message: " << chat_message << '\n';

                    chat_box.AddUserData(chat_message);

                    liboai::Response response = open_ai.ChatCompletion->create("gpt-4o-mini", chat_box);

                    chat_box.Update(response);

                    // Send a confirmation message
                    ws.write(asio::buffer(chat_box.GetLastResponse()));
                    std::cout << "Confirmation sent to client\n";

                    buffer.consume(buffer.size());  // Clear the buffer for the next message
                }
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << '\n';
            }
        }
    }
    catch(const std::exception& e){
        std::cout << e.what() << '\n';
    }
}

int main() {
    try {
        asio::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "WebSocket server listening on port 8080..." << std::endl;

        while (true) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);  // Wait for a client to connect

            std::thread(&reply, std::move(socket)).detach();
        }
    } catch (const std::exception& e) {
        std::cout << "Server Error: " << e.what() << std::endl;
    }
}
