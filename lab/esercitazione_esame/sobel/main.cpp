#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;

Mat sobelXY(Mat src, int ddepth, int xON, int yON) {
    Mat dst = src;
    copyMakeBorder(src, src, 1, 1, 1, 1, BORDER_DEFAULT,Scalar(0));
    float sobelX[] = {
        -1.0, -2.0, -1.0,
        0.0, 0.0, 0.0,
        1.0, 2.0, 1.0
    };
    float sobelY[] = {
        -1.0, 0.0, 1.0,
        -2.0, 0.0, 2.0,
        -1.0, 0.0, 1.0
    };
    Mat maskX(3, 3,CV_32F, sobelX);
    Mat maskY(3, 3,CV_32F, sobelY);
    if (xON && !yON) {
        filter2D(src, dst, ddepth, maskX);
    }
    if (!xON && yON) {
        filter2D(src, dst, ddepth, maskY);
    }

    if (xON && yON) {
        Mat imgSobelX = sobelXY(src, ddepth, 1, 0);
        Mat imgSobelY = sobelXY(src, ddepth, 0, 1);
        dst = abs(imgSobelX) + abs(imgSobelY);
    }
    return dst;
}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "a.jpeg";
    cv::Mat m = cv::imread(cv::samples::findFile(imageName), IMREAD_GRAYSCALE);

    Mat m2 = sobelXY(m,CV_8UC1, 1, 1);
    imshow("sobel mio", m2);
    // Mat m2 = sobelXY(m,CV_8UC1,1,1);
    Mat m3(m.rows, m.cols, m.type());
    Sobel(m, m3,CV_8UC1, 1, 0);
    Sobel(m, m3,CV_8UC1, 0, 1);
    imshow("sobel", m3);
    waitKey(0);
    return 0;
}
