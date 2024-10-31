#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

void myHoughCircles(Mat &src, Mat &dst, int lth, int hth, int gaussSize) {
    copyMakeBorder(src, src, gaussSize / 2, gaussSize / 2, gaussSize / 2, gaussSize / 2, BORDER_DEFAULT, Scalar(0));
    Mat gausMat = src.clone();
    GaussianBlur(src, gausMat, Size(gaussSize, gaussSize), 0, 0);
    Mat edgeCanny = gausMat.clone();
    Canny(gausMat, edgeCanny, lth, hth, 3);

    int r_min = 60;
    int r_max = 90;
    int theta;
    int sizes[3] = {edgeCanny.rows, edgeCanny.cols, r_max - r_min + 1};
    Mat votes = Mat::zeros(3, sizes, CV_8U);
    for (int x = 0; x < edgeCanny.rows; x++) {
        for (int y = 0; y < edgeCanny.cols; y++) {
            if (edgeCanny.at<uchar>(x, y) == 255) {
                for (int r = r_min; r <= r_max; r++) {
                    for (theta = 0; theta < 360; theta++) {
                        int a = x - r * sin(theta * M_PI / 180);
                        int b = y - r * cos(theta * M_PI / 180);
                        if (a >= 0 && a < edgeCanny.rows && b >= 0 && b < edgeCanny.cols) {
                            votes.at<uchar>(a, b, r - r_min)++;
                        }
                    }
                }
            }
        }
    }

    for (int r = r_min; r <= r_max; r++) {
        for (int a = 0; a < edgeCanny.rows; a++) {
            for (int b = 0; b < edgeCanny.cols; b++) {
                if(votes.at<uchar>(a,b,r-r_min) >= 90){
                    circle(dst,Point(b,a),3,Scalar(0),2,8,0);
                    circle(dst,Point(b,a),r,Scalar(0),2,8,0);
                }
            }
        }
    }
}
    int main(int argc, char **argv) {
        const char *imageName = argc >= 2 ? argv[1] : "../immagini/monete.png";
        Mat src = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
        Mat dst = src.clone();
        myHoughCircles(src, dst, 150, 230, 9);
        imshow("hough", dst);
        waitKey(0);
    }
