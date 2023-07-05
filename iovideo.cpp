#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include <sstream>
using namespace std;
using namespace cv;

int main(int, char** argv){
    //Create a writer
    FileStorage fs("test.yml", FileStorage::WRITE);
    int fps =5;
    fs << "fps " <<fps;


    return 0;
}