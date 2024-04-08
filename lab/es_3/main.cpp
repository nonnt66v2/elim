//
// Created by nonnt66 on 08/04/24.
//
// Description:
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;


void cv::copyMakeBorder(
        cv::InputArray src,
        cv::OutputArray dst,
        int top,
        int bottom,
        int left,
        int right,
        int borderType,
        const cv::Scalar &value = cv::Scalar()
);

int main(){
    cv::Mat img = cv::imread("1.png", IMREAD_COLOR);
    if(img.empty()){
        cout << "Could not read the image: " << "1.png" << std::endl;
        return 1;
    }
    cv::namedWindow("Display window", WINDOW_AUTOSIZE);
    cv::imshow("Display window", img);
    cv::waitKey(0);
    return 0;

}

