//
// Created by Naren Sadhwani on 26.01.23.
//
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void cartoonifyImage(Mat srcColor, Mat dst)
{
    // Convert from BGR color to Grayscale
    Mat srcGray;
    cvtColor(srcColor, srcGray, COLOR_BGR2GRAY);

    // Remove the pixel noise with a good Median filter, before we start detecting edges.
    medianBlur(srcGray, srcGray, 7);

    Size size = srcColor.size();
    Mat mask = Mat(size, CV_8U);
    Mat edges = Mat(size, CV_8U);

    // Generate a nice edge mask, similar to a pencil line drawing.
    Laplacian(srcGray, edges, CV_8U, 5);
    threshold(edges, mask, 80, 255, THRESH_BINARY_INV);
    // Mobile cameras usually have lots of noise, so remove small
    // dots of black noise from the black & white edge mask.

//    else {
//        // Evil mode, making everything look like a scary bad guy.
//        // (Where "srcGray" is the original grayscale image plus a medianBlur of size 7x7).
//        Mat edges2;
//        Scharr(srcGray, edges, CV_8U, 1, 0);
//        Scharr(srcGray, edges2, CV_8U, 1, 0, -1);
//        edges += edges2;
//        threshold(edges, mask, 12, 255, THRESH_BINARY_INV);
//        medianBlur(mask, mask, 3);
//    }
    //imshow("edges", edges);
    //imshow("mask", mask);

    // For sketch mode, we just need the mask!
//    if (sketchMode) {
//        // The output image has 3 channels, not a single channel.
//        cvtColor(mask, dst, COLOR_BGR2GRAY);
//        return;
//    }

    // Do the bilateral filtering at a shrunken scale, since it
    // runs so slowly but doesn't need full resolution for a good effect.
    Size smallSize;
    smallSize.width = size.width/2;
    smallSize.height = size.height/2;
    Mat smallImg = Mat(smallSize, CV_8UC3);
    resize(srcColor, smallImg, smallSize, 0,0, INTER_LINEAR);

    // Perform many iterations of weak bilateral filtering, to enhance the edges
    // while blurring the flat regions, like a cartoon.
    Mat tmp = Mat(smallSize, CV_8UC3);
    int repetitions = 7;        // Repetitions for strong cartoon effect.
    for (int i=0; i<repetitions; i++) {
        int size = 9;           // Filter size. Has a large effect on speed.
        double sigmaColor = 9;  // Filter color strength.
        double sigmaSpace = 7;  // Positional strength. Effects speed.
        bilateralFilter(smallImg, tmp, size, sigmaColor, sigmaSpace);
        bilateralFilter(tmp, smallImg, size, sigmaColor, sigmaSpace);
    }

//    if (alienMode) {
//        // Apply an "alien" filter, when given a shrunken image and the full-res edge mask.
//        // Detects the color of the pixels in the middle of the image, then changes the color of that region to green.
//        changeFacialSkinColor(smallImg, edges, debugType);
//    }

    // Go back to the original scale.
    resize(smallImg, srcColor, size, 0,0, INTER_LINEAR);

    // Clear the output image to black, so that the cartoon line drawings will be black (ie: not drawn).
    memset((char*)dst.data, 0, dst.step * dst.rows);

    // Use the blurry cartoon image, except for the strong edges that we will leave black.
    srcColor.copyTo(dst, mask);
}

/////////////////  Webcam  //////////////////////



int cameraNumber = 0;

// Get access to the camera.
VideoCapture camera;


int main(){
    camera.open(cameraNumber);
    if(!camera.isOpened()){
        cerr<< "Error: Could not access the camera or video!"<<endl;
        exit(1);
    }

    //Try to set camera resolution
    camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    while(true) {
        Mat cameraFrame;
        camera >> cameraFrame;
        if (cameraFrame.empty()) {
            std::cerr << "ERROR: Couldn't grab a camera frame." <<
                      std::endl;
            exit(1);
        }
        Mat displayedFrame(cameraFrame.size(), CV_8UC3);
        Mat gray;
        cartoonifyImage(cameraFrame, displayedFrame);
        imshow("Cartoonifier", cameraFrame);
        char keypress = waitKey(20);
        if (keypress == 27) {
            break;
        }
    }
}







