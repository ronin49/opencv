#include <opencv2/opencv.hpp>
#include "sobol.h"

int main() {
    // Initialize the camera capture object
    cv::VideoCapture cap(0);  // Use 0 for the default camera (usually the built-in webcam)

    // Check if the camera is opened successfully
    if (!cap.isOpened()) {
        std::cout << "Error: Unable to open the camera." << std::endl;
        return -1;
    }

    // Main loop to read frames from the camera and display them
    while (true) {
        cv::Mat frame;
        
        // Capture frame-by-frame
        cap >> frame;
        
        // Check if the frame is read correctly
        if (frame.empty()) {
            std::cout << "Error: Unable to read frame." << std::endl;
            break;
        }
        
	cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
	sobol(frame,frame);
        // Display the frame
        cv::imshow("Camera Feed", frame);
        
        // Check for the 'ESC' key press to exit the loop
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    // Release the camera capture object
    cap.release();
    
    // Close all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}

