#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <cmath>

using namespace cv;

void HoughCerchi(Mat &src, Mat &dst, int th) {
    int padding = 3 / 2;
    copyMakeBorder(src, src, padding, padding, padding, padding, 0);
    Mat gsbl;
    GaussianBlur(src, gsbl, Size(7, 7), 0, 0);
    Mat edges;
    Canny(gsbl, edges, 40, 90);
    int Rmin = 30;
    int Rmax = 90;
//    int votes[edges.rows][edges.cols][Rmax - Rmin];
    
    int sizes[3] = {edges.rows, edges.cols, Rmax - Rmin + 1};
    Mat votes = Mat::zeros(3, sizes, CV_8U);
    double theta;
    int a, b;
    double pi = CV_PI / 180;
    for (int y = 0; y < edges.rows; y++) {   //y
        for (int x = 0; x < edges.cols; x++) {    //x
            if (edges.at<uchar>(y, x) == 255) {
                for (int r = Rmin; r < Rmax; r++) {
                    for (theta = 0; theta < 360; theta++) {
//                        theta-=180;
                        // a = x -r(theta)
                        a = x - r * cos(theta*pi);
                        b = y - r * sin(theta*pi);
                        if (a >= 0 && a < edges.cols && b >= 0 && b < edges.rows) {
                            votes.at<uchar>(b, a, r - Rmin)++;
                        }
                    }
                }
            }
        }
    }
    dst = src.clone();
    for (int r = Rmin; r < Rmax; r++) {
        for (int y = 0; y < edges.rows; y++) {
            for (int x = 0; x < edges.cols; x++) {
                if (votes.at<uchar>(y, x,r-Rmin) > th) {
                    circle(dst, Point(x, y), 3, 0, 1, 4, 0);
                    circle(dst, Point(x, y), r, 0, 1, 4, 0);
                }
            }
        }
    }


}

int main(int argc, char **argv) {
    const char *Imagename = argc > 1 ? argv[1] : "../immagini/monete.png";
    Mat m = imread(samples::findFile(Imagename), IMREAD_GRAYSCALE);
    imshow("start", m);
    waitKey(1);
    HoughCerchi(m, m, 120);
    imshow("hough", m);
    waitKey(0);
}
