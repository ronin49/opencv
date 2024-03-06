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

    // Display the original image
    imshow("Original Image", image);
    waitKey(0);

    // Resize the image
    int new_width = 300;
    int new_height = 200;
    Mat resized_image;
    resize(image, resized_image, Size(new_width, new_height));

    // Display the resized image
    imshow("Resized Image", resized_image);
    waitKey(0);

    // Define the region of interest (ROI) coordinates
    int x = 100, y = 100, width = 200, height = 200;

    // Crop the image
    Mat cropped_image = image(Rect(x, y, width, height));

    // Display the cropped image
    imshow("Cropped Image", cropped_image);
    waitKey(0);

    // Define the rotation angle
    double angle = 45;

    // Get the image center
    Point2f center(image.cols / 2.0, image.rows / 2.0);

    // Perform the rotation
    Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    Mat rotated_image;
    warpAffine(image, rotated_image, rotation_matrix, image.size());

    // Display the rotated image
    imshow("Rotated Image", rotated_image);
    waitKey(0);

    // Apply Gaussian blur
    int kernel_size = 5;
    Mat blurred_image;
    GaussianBlur(image, blurred_image, Size(kernel_size, kernel_size), 0);

    // Display the blurred image
    imshow("Blurred Image", blurred_image);
    waitKey(0);

    // Convert BGR to Grayscale
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    // Display the grayscale image
    imshow("Grayscale Image", gray_image);
    waitKey(0);

    // Draw a rectangle
    rectangle(image, Point(x, y), Point(x+width, y+height), Scalar(0, 255, 0), 2);

    // Draw a circle
    int center_x = 200, center_y = 200, radius = 50;
    circle(image, Point(center_x, center_y), radius, Scalar(0, 0, 255), 2);

    // Put text
    putText(image, "OpenCV", Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

    // Display the image with shapes and text
    imshow("Image with Shapes and Text", image);
    waitKey(0);

    // Close all windows
    destroyAllWindows();

    return 0;
}

