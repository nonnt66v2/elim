//
// Created by nonnt66 on 15/04/24.
//
#include <stdlib.h>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

void correlazione(cv::Mat *k, cv::Mat *m, int k_rows, int k_cols, int x, int y) {
    float somma = 0;
    for (int s = 0; s < k_rows; s++) {
        for (int t = 0; t < k_cols; t++) {
            somma += ((k->at<float>(s, t) * m->at<float>(x + s, y + t)));
        }
    }
    m->at<float>(x, y) = somma;
}

int main() {
    cv::Mat m = cv::Mat::zeros(10, 10, CV_32F);
    //cv::randu(m, 0, 1);
    m.at<float>(5, 5) = 1;
    std::cout << m << std::endl;
    copyMakeBorder(m, m, 3, 3, 3, 3, 0);
//    std::cout << m << std::endl;
    ///creo la maschera
    cv::Mat k(3, 3, CV_32F);
    int tmp = 1;
    for (int i = 0; i < k.cols; ++i) {
        for (int j = 0; j < k.rows; ++j) {
            k.at<float>(i, j) = (float) tmp++;
        }
    }
    std::cout << m.at<float>(6, 6) << std::endl;


    ///accedo a tutti gli intorni dei pixel della maschera
    for (int i = 1; i < m.rows - 1; i++) {
        for (int j = 1; j < m.cols - 1; j++) {
            correlazione(&k, &m, k.rows, k.cols, i, j);
        }
    }
    std::cout << m << std::endl;
    m = cv::Mat::zeros(10, 10, CV_32F);
    m.at<float>(5, 5) = 1;
//   std::cout << m << std::endl;
    copyMakeBorder(m, m, 1, 1, 1, 1, 0);
    filter2D(m, m, CV_32F, k, cv::Point(-1, -1), 0, BORDER_DEFAULT);

    std::cout << m << std::endl;


}

