#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Load the pre-trained Haar cascade for face detection
    CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_alt.xml");

    // Read the input image
    Mat image = imread("image.jpg");

    // Convert the image to grayscale
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    // Detect faces in the image
    vector<Rect> faces;
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 3, 0, Size(30, 30));

    // Draw rectangles around the detected faces
    for (size_t i = 0; i < faces.size(); i++) {
        rectangle(image, faces[i], Scalar(255, 0, 0), 2);
    }

    // Display the image with detected faces
    imshow("Detected Faces", image);
    waitKey(0);

    return 0;
}

