//
// Created by Naren Sadhwani on 28.01.23.
//


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

///////////////  Warp Images  //////////////////////

int main() {

    string path = "/Users/mcking/C++_Projects/opencv/opencv/opencv/Resources/cards.jpg";
    Mat img = imread(path);
    Mat matrix, imgWarp;
    float w = 250, h = 350;

    Point2f src[4] = {{529, 142},
                      {771, 190},
                      {405, 395},
                      {674, 457}};
    Point2f dst[4] = {{0.0f, 0.0f},
                      {w,    0.0f},
                      {0.0f, h},
                      {w,    h}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    for (int i = 0; i < 4; i++) {
        circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
    }

    imshow("Image", img);
    imshow("Image Warp", imgWarp);
    waitKey(0);

    return 0;

}