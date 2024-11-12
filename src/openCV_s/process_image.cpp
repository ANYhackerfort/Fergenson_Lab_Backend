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
void ImageProcessor::detectMinMax(double lowerThreshold, double upperThreshold){
    cv::Mat thresh;
    cv::threshold(grayImage, thresh, lowerThreshold, upperThreshold, cv::THRESH_BINARY_INV);
    tesseract::TessBaseAPI tess;
    if (tess.Init(NULL, "eng", tesseract::OEM_LSTM_ONLY)) {
        std::cerr << "Could not initialize Tesseract OCR." << std::endl;
        return;
    }
    tess.SetPageSegMode(tesseract::PSM_SPARSE_TEXT);
    tess.SetImage(thresh.data, thresh.cols, thresh.rows, 1, thresh.step);
    char* outText = tess.GetUTF8Text();
    std::string text(outText);
    std::cout << "Detected Text: " << text << std::endl;
    tess.End();
    delete[] outText;

    // Process the extracted text to find numeric values
    std::istringstream iss(text);
    std::string word;
    std::vector<int> numbers;
     while (iss >> word) {
        try {
            int num = std::stoi(word);
            numbers.push_back(num);
        } catch (std::invalid_argument& e) {
            // Not a number, skip
        }
    }

    // If numbers were detected, find the min and max values
    if (!numbers.empty()) {
        int min_value = *std::min_element(numbers.begin(), numbers.end());
        int max_value = *std::max_element(numbers.begin(), numbers.end());
        std::cout << "Minimum Value: " << min_value << ", Maximum Value: " << max_value << std::endl;
    } else {
        std::cout << "No numbers detected." << std::endl;
    }
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
