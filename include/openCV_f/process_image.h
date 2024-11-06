#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <string>
#include <opencv2/opencv.hpp>


class ImageProcessor {
public:
    // Constructor that takes an image path
    ImageProcessor(const std::string& imagePath);

    // Method to load the image
    bool loadImage();

    // Method to convert the image to grayscale
    void convertToGrayscale();

    // Method to apply edge detection
    void detectEdges(double lowerThreshold = 50.0, double upperThreshold = 150.0);

    // Method to display images
    void displayImages() const;
    cv::Mat getEdges() const { return edges; }

private:
    cv::Mat originalImage; // Original loaded image
    cv::Mat grayImage;     // Grayscale version of the image
    cv::Mat edges;         // Edge-detected image
    std::string imagePath; // Path to the image file
};

#endif // IMAGEPROCESSOR_H
