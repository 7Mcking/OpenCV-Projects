//
// Created by Naren Sadhwani on 28.01.23.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


///////////////  Basic Functions  //////////////////////

int main() {

    string path = "/Users/mcking/C++_Projects/opencv/opencv/opencv/Resources/cards.jpg";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
    imshow("Image", img);

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
    Canny(imgBlur, imgCanny, 25,75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    erode(imgDil, imgErode, kernel);


    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil);
    imshow("Image Erode", imgErode);
    waitKey(0);

    return 0;
}