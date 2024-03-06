#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main() {
    // Create a sample dataset for classification
    Mat trainingData = (Mat_<float>(4, 2) << 1.0, 1.0, 2.0, 2.0, 8.0, 8.0, 9.0, 10.0);
    Mat labels = (Mat_<int>(4, 1) << 0, 0, 1, 1);

    // Train a k-Nearest Neighbors (k-NN) classifier
    Ptr<KNearest> knn = KNearest::create();
    knn->train(trainingData, ROW_SAMPLE, labels);

    // Test the classifier with new data
    Mat testData = (Mat_<float>(1, 2) << 3.0, 3.0);
    Mat results;
    knn->findNearest(testData, 1, results);

    // Output the predicted label
    cout << "Predicted label: " << results.at<float>(0, 0) << endl;

    return 0;
}

