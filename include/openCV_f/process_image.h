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

    // Method to apply Gaussian blur for noise reduction
    void removeNoise(); 
    void preprocessForOCR();

    // Getter for the Gaussian-blurred image
    cv::Mat getGaussianImage() const { return gaussianImage; }
    cv::Mat getGrayScaleImage() const {return grayImage; }
    cv::Mat getPreproccessed_ocr() const {return preproccessed_ocr; }


private:
    cv::Mat originalImage; // Original loaded image
    cv::Mat grayImage;     // Grayscale version of the image
    cv::Mat edges;         // Edge-detected image
    cv::Mat gaussianImage; // Gaussian-blurred image (noise-reduced)
    cv::Mat preproccessed_ocr; 
    std::string imagePath; // Path to the image file
};

#endif // IMAGEPROCESSOR_H
