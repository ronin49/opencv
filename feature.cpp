#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Read an image from file
    Mat image = imread("image.jpg");

    // Check if the image is loaded successfully
    if(image.empty()) {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    // Detect keypoints using ORB (Oriented FAST and Rotated BRIEF)
    Ptr<Feature2D> orb = ORB::create();
    vector<KeyPoint> keypoints;
    orb->detect(gray_image, keypoints);

    // Compute descriptors for the keypoints using ORB
    Mat descriptors;
    orb->compute(gray_image, keypoints, descriptors);

    // Draw keypoints on the original image
    Mat image_with_keypoints;
    drawKeypoints(image, keypoints, image_with_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

    // Display the image with keypoints
    imshow("Image with Keypoints", image_with_keypoints);
    waitKey(0);

    // Close all windows
    destroyAllWindows();

    return 0;
}

