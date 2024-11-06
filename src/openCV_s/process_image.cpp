#include "process_image.h"
#include <iostream>

ImageProcessor::ImageProcessor(const std::string& imagePath) : imagePath(imagePath) {}

bool ImageProcessor::loadImage() {
    originalImage = cv::imread(imagePath);
    if (originalImage.empty()) {
        std::cerr << "Could not open or find the image at: " << imagePath << std::endl;
        return false;
    }
    return true;
}

void ImageProcessor::convertToGrayscale() {
    cv::cvtColor(originalImage, grayImage, cv::COLOR_BGR2GRAY);
}

void ImageProcessor::detectEdges(double lowerThreshold, double upperThreshold) {
    cv::Canny(grayImage, edges, lowerThreshold, upperThreshold);
}

void ImageProcessor::displayImages() const {
    if (!grayImage.empty()) {
        cv::imshow("Grayscale Image", grayImage);
    }
    if (!edges.empty()) {
        cv::imshow("Edge Detection", edges);
    }
    cv::waitKey(0);
}
