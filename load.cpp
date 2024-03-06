#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Load an image from file
    cv::Mat image = cv::imread("Downloads/photo1709643757.jpeg");

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Display the loaded image
    cv::imshow("Loaded Image", image);

    // Wait for a keystroke
    cv::waitKey(0);

    return 0;
}

