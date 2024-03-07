#include <opencv2/opencv.hpp>
#include <obs-module.h> // Include OBS headers for the virtual camera functionality

int main() {
    // Open the camera
    cv::VideoCapture cap(0); // Change the parameter to the appropriate camera index if necessary

    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }

    // Create a virtual camera (assuming OBS Virtual Camera)
    obs_module_load();

    obs_output_t *virtualCam = obs_output_create("obs-virtualcam", "OBS Virtual Camera", nullptr, nullptr);

    // Set up the virtual camera resolution
    obs_data_t *settings = obs_output_get_settings(virtualCam);
    obs_data_set_int(settings, "width", 640); // Adjust width as needed
    obs_data_set_int(settings, "height", 480); // Adjust height as needed
    obs_data_set_int(settings, "fps_num", 30); // Adjust fps as needed
    obs_output_update(virtualCam, settings);

    // Main loop
    cv::Mat frame;
    while (true) {
        cap >> frame;

        // If frame is empty, break the loop
        if (frame.empty()) {
            std::cerr << "Failed to capture frame" << std::endl;
            break;
        }

        // Process the frame if necessary
        // e.g., cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        // Send the frame to the virtual camera
        // OBS virtual camera requires BGR format
        obs_output_video_frame(virtualCam, frame.data, frame.step[0], frame.cols, frame.rows);

        // Show the frame (optional)
        cv::imshow("Frame", frame);

        // Break the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release resources
    obs_output_release(virtualCam);
    obs_module_unload();

    cap.release();
    cv::destroyAllWindows();

    return 0;
}

