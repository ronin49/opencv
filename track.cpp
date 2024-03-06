#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Read the first frame from the video
    VideoCapture cap("video.mp4");
    if (!cap.isOpened()) {
        cout << "Error: Failed to open the video file." << endl;
        return -1;
    }

    Mat frame;
    cap >> frame;

    // Define the initial tracking window
    Rect track_window(200, 100, 100, 100);

    // Convert the first frame to HSV color space
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    // Mask out the region of interest (ROI) for tracking
    Mat mask;
    inRange(hsv, Scalar(0, 60, 32), Scalar(180, 255, 255), mask);
    Mat roi(mask, track_window);

    // Calculate the histogram of the ROI
    Mat hist;
    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    float hranges[] = {0, 180};
    float sranges[] = {0, 256};
    const float* ranges[] = {hranges, sranges};
    int channels[] = {0, 1};
    calcHist(&hsv, 1, channels, roi, hist, 2, histSize, ranges, true, false);

    // Normalize the histogram
    normalize(hist, hist, 0, 255, NORM_MINMAX);

    // Term criteria for MeanShift algorithm
    TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);

    // Perform object tracking using MeanShift
    while (true) {
        // Read a new frame from the video
        cap >> frame;
        if (frame.empty())
            break;

        // Convert the frame to HSV color space
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // Calculate the back projection of the histogram
        Mat backproj;
        calcBackProject(&hsv, 1, channels, hist, backproj, ranges, 1, true);

        // Apply MeanShift to track the object
        RotatedRect track_box = meanShift(backproj, track_window, term_crit);

        // Draw the tracked object on the frame
        ellipse(frame, track_box, Scalar(0, 255, 0), 2);

        // Display the frame with the tracked object
        imshow("Object Tracking", frame);

        // Wait for the 'Esc' key to exit
        if (waitKey(30) == 27)
            break;
    }

    // Release the video capture object and close all windows
    cap.release();
    destroyAllWindows();

    return 0;
}

