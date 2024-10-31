#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

void myHoughLines(Mat &src, Mat &dst, int ksize, int lth, int hth) {
    copyMakeBorder(src, src, ksize / 2, ksize / 2, ksize / 2, ksize / 2, BORDER_DEFAULT, Scalar(0));
    GaussianBlur(src, src, Size(5, 5),0,0);
    Mat edgeCanny = src.clone();
    Canny(src, edgeCanny, lth, hth, 3);
    imshow("Canny", edgeCanny);
    waitKey(0);
    double theta;
    double rho;

    int ipotenusa = hypot(src.rows, src.cols);
    Mat votes = Mat::zeros(ipotenusa * 2, 180, CV_8U);

    for (int x = 0; x < edgeCanny.rows; x++) {
        for (int y = 0;y < edgeCanny.cols; y++) {
            if (edgeCanny.at<uchar>(x,y) == 255) {
                for (theta = 0; theta < 180; theta++) {
                    rho = ipotenusa + y * cos((theta - 90) * CV_PI / 180) + x * sin((theta - 90) * CV_PI / 180);
                    votes.at<uchar>(rho, theta)++;
                }
            }
        }
    }

    imshow("voti", votes);
    waitKey(0);

    for(int r=0;r<votes.rows;r++){
        for(int t=0;t<votes.cols;t++){
            if(votes.at<uchar>(r,t) >= lth){
                theta = (t-90) * CV_PI/180;
                int x = (r-ipotenusa)*cos(theta);
                int y = (r-ipotenusa)*sin(theta);
                double sin_t = sin(theta);
                double cos_t = cos(theta);
                Point p1(cvRound(x+ipotenusa*(-sin_t)), cvRound(y+ipotenusa*(cos_t)));
                Point p2(cvRound(x-ipotenusa*(-sin_t)), cvRound(y-ipotenusa*(cos_t)));
                line(src,p1,p2,Scalar(200),1,0);
            }
        }
    }


}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "../immagini/bw.png";
    Mat src = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
    Mat dst = src.clone();
    myHoughLines(src, dst, 3, 90, 150);
    imshow("Hough lines", src);
    waitKey(0);
}
