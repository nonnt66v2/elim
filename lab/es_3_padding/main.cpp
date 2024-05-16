#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
#include "opencv2/core/matx.hpp"
#include <opencv2/core/types.hpp>

using namespace cv;
using namespace std;

int main() {

    int rows = 3;
    int cols = 3;
    cv::Mat m = cv::Mat::zeros(rows, cols, CV_32F);
    cv::Mat m2;
    cv::randu(m, 0.0f, 0.1f); // fill matrix with random values in range [-1.0, 1.0]
//    std::cout << m << std::endl;

    std::cout<<m<<std::endl;
    copyMakeBorder(m, m, 1, 1, 1, 1, cv::BORDER_CONSTANT, cv::Scalar(0));
    std::cout<<m<<std::endl;
    //Sostituire al valore di ogni pixel il valore medio dei livelli di grigio in un intorno 3x3

    for (int i = 1; i < m.rows-1; i++) {
        for (int j = 1; j < m.cols-1; j++) {
            float sum = 0;
            for (int k = -1; k < 2; k++) {
                for (int l = -1; l < 2; l++) {
                    sum += m.at<float>(i+k, j+l);
                }
            }
            m.at<float>(i, j) = sum/9;
        }
    }
    std::cout<<m<<std::endl;
    cv::Canny(m, m2, 0.1, 0.2);
    std::cout<<m2<<std::endl;
    return 0;




}
// Compile: g++ main.cpp -o main `pkg-config --cflags --libs opencv4` && ./main
