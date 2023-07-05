#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//Opencv Includes
#include <opencv2/opencv.hpp>
using namespace cv;

int main(){
    Mat colorImg = imread("../Resources/cards.jpg");
    Mat grayImage;
    cvtColor(colorImg, grayImage, CV_16F);

    if (!colorImg.data){
        cout<<"Could not open of find the image"<< endl;
        return -1;
    }
    imwrite("cards_gray.png", grayImage);

    int myRow = colorImg.cols -1;
    int myCol = colorImg.rows -1;
    Vec3b pixel = colorImg.at<Vec3b>(myRow, myCol);
    cout <<"Pixel Value(B,G,R) :("<< (int)pixel[0] <<"," <<(int)pixel[1] << ","
    << (int)pixel[2] <<")"<< endl;
    //Show images
    imshow("Colored Cards", colorImg);
    imshow("Cards Gray", grayImage);

    waitKey(0);
    return 0;
}