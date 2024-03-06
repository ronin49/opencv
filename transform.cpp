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

    // Scale transformation
    double scale_factor = 0.5;
    Mat scaled_image;
    resize(image, scaled_image, Size(), scale_factor, scale_factor);

    // Display the scaled image
    imshow("Scaled Image", scaled_image);
    waitKey(0);

    // Rotation transformation
    double angle = 45;
    Point2f center(image.cols / 2.0, image.rows / 2.0);
    Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    Mat rotated_image;
    warpAffine(image, rotated_image, rotation_matrix, image.size());

    // Display the rotated image
    imshow("Rotated Image", rotated_image);
    waitKey(0);

    // Translation transformation
    int dx = 50, dy = 50;
    Mat translation_matrix = (Mat_<double>(2,3) << 1, 0, dx, 0, 1, dy);
    Mat translated_image;
    warpAffine(image, translated_image, translation_matrix, image.size());

    // Display the translated image
    imshow("Translated Image", translated_image);
    waitKey(0);

    // Perspective transformation
    vector<Point2f> src_points, dst_points;
    src_points.push_back(Point2f(0, 0));
    src_points.push_back(Point2f(image.cols - 1, 0));
    src_points.push_back(Point2f(0, image.rows - 1));
    src_points.push_back(Point2f(image.cols - 1, image.rows - 1));

    dst_points.push_back(Point2f(100, 100));
    dst_points.push_back(Point2f(image.cols - 100, 150));
    dst_points.push_back(Point2f(50, image.rows - 50));
    dst_points.push_back(Point2f(image.cols - 50, image.rows - 50));

    Mat perspective_matrix = getPerspectiveTransform(src_points, dst_points);
    Mat perspective_transformed_image;
    warpPerspective(image, perspective_transformed_image, perspective_matrix, image.size());

    // Display the perspective transformed image
    imshow("Perspective Transformed Image", perspective_transformed_image);
    waitKey(0);

    // Close all windows
    destroyAllWindows();

    return 0;
}

