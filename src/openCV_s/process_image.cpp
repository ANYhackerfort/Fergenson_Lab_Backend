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

void ImageProcessor::removeNoise() {
    //stud
}

void ImageProcessor::preprocessForOCR() {
    // Check if grayscale conversion is needed
    if (grayImage.empty()) {
        this->convertToGrayscale();
    }

    // Apply adaptive thresholding
    cv::Mat adaptiveThresholdImage;
    cv::adaptiveThreshold(grayImage, adaptiveThresholdImage, 255, 
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);

    // // Remove small dots using morphological opening
    // cv::Mat morphElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
    // cv::morphologyEx(adaptiveThresholdImage, adaptiveThresholdImage, cv::MORPH_OPEN, morphElement);

    // Perform dilation to make text bolder (optional for OCR)
    cv::dilate(adaptiveThresholdImage, preproccessed_ocr, cv::Mat(), cv::Point(-1, -1), 1);
}



