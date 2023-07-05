// OpenCV includes
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
// For each of the 3 sides of the triangle
for (int i = 0; i < 3; i++) {
    // Calculate the distance between the 2 points
    float dx = pt[i].x - pt[(i + 1) % 3].x;
    float dy = pt[i].y - pt[(i + 1) % 3].y;
    float dist = sqrt(dx * dx + dy * dy);

    // Calculate the angle of the 2 sides relative to the x axis
    float angle1 = atan2(dy, dx);
    float angle2 = atan2(dy, dx);

    // Calculate the angle between the 2 sides
    float angle = angle1 - angle2;

    // If the angle is over 180 degrees, subtract 360 degrees
    if (angle > 3.14159) {
        angle -= 6.28318;
    }

    // If the angle is under -180 degrees, add 360 degrees
    else if (angle < -3.14159) {
        angle += 6.28318;
    }

    // Calculate the angle between the 2 sides
    angle = fabs(angle);

    // Calculate the radius of the circle
    float radius = dist / (2 * sin(angle / 2));

    // Calculate the center point of the circle
    float centerX = (pt[i].x + pt[(i + 1) % 3].x) / 2;
    float centerY = (pt[i].y + pt[(i + 1) % 3].y) / 2;

    // Calculate the distance between the center point and one of the points
    dx = pt[i].x - centerX;
    dy = pt[i].y - centerY;
    float centerDist = sqrt(dx * dx + dy * dy);

    // Calculate the distance between the center point and one of the points
    if (centerDist > radius) {
        // The center point is outside the circle
        return false;
    }
}
return true;
// Create a variable to save the position value in track
int blurAmount=15;

// Trackbar call back function
static void onChange(int pos, void* userData);


//Mouse callback
static void onMouse(int event, int x, int y, int, void* userInput);


int main(int argc, const char** argv)
{
    // Read images
    Mat lena= imread("/Users/mcking/C++_Projects/opencv/opencv/opencv/Resources/paper.jpg");

    // Create windows
    namedWindow("Lena");

    // create a trackbar
    createTrackbar("Lena", "Lena", &blurAmount, 30, onChange, &lena);

    setMouseCallback("Lena", onMouse, &lena);

    // Call to onChange to init
    onChange(blurAmount, &lena);

    // wait app for a key to exit
    waitKey(0);

    // Destroy the windows
    destroyWindow("Lena");

    return 0;
}
static void onChange(int pos, void* userData) {
    if(pos <= 0) return;
    // Aux variable for result
    Mat imgBlur;
    // Get the pointer input image
    Mat* img= (Mat*)userData;
    // Apply a blur filter
    blur(*img, imgBlur, Size(pos, pos));
    // Show the result
    imshow("Lena", imgBlur);
}

static void onMouse(int event, int x, int y, int, void* userInput)
{
    if(event != EVENT_LBUTTONDOWN)
        return;

    // Get the pointer input image
    Mat* img= (Mat*)userInput;

    // Draw circle
    cv::circle(*img, Point(x, y), 10, Scalar(0,255,0), 3);

    // Call on change to get blurred image
    onChange(blurAmount, img);

}
