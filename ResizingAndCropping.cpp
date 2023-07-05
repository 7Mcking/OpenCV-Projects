//
// Created by Naren Sadhwani on 28.01.23.
//


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


///////////////  Resize and Crop //////////////////////

int main() {

    string path = "/Users/mcking/C++_Projects/opencv/opencv/opencv/Resources/cards.jpg";
    Mat img = imread(path);
    Mat imgResize, imgCrop;

    cout << img.size() << endl;
    resize(img, imgResize, Size(),0.5,0.5);

    Rect roi(200, 100, 300, 300);
    imgCrop = img(roi);

    imshow("Image", img);
    imshow("Image Resize", imgResize);
    imshow("Image Crop", imgCrop);
    waitKey(0);
    return 0;
}