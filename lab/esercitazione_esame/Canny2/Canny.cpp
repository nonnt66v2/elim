#include "opencv4/opencv2/opencv.hpp"
#include <stdlib.h>

using namespace cv;

void isteresis_thresholding(Mat nms, int lth, int hth, Mat &dst) {
    for (int i = 1; i < nms.rows - 1; i++) {
        for (int j = 1; j < nms.cols - 1; i++) {
            if (nms.at<uchar>(i, j) > hth) {
                dst.at<uchar>(i, j) = 255;
                for (int u = -1; u < 1; u++) {
                    for (int v = -1; v < 1; v++) {
                        if (nms.at<uchar>(i + u, j + v) > lth && nms.at<uchar>(i + u, j + v) < hth) {
                            dst.at<uchar>(i + u, j + v) = 255;
                        }
                    }
                }

            } else if (nms.at<uchar>(i, j) < lth) {
                dst.at<uchar>(i, j) = 0;
            }
        }
    }
}

void NMS(Mat mag, Mat orientation, Mat &nms) {
    for (int i = 1; i < mag.rows - 1; i++) {
        for (int j = 1; j < mag.cols - 1; i++) {
            float angolo = orientation.at<float>(i, j);
            if (angolo > 180) angolo -= 360;
            if ((22.5 <= angolo) && (angolo < -22.5) || (-157.5 <= angolo) && (angolo < 157.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i - 1, j) && mag.at<uchar>(i, j) > mag.at<uchar>(i + 1, j)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            }
            if ((-22.5 <= angolo) && (angolo < -67.5) || (112.5 <= angolo) && (angolo < 157.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i + 1, j - 1) &&
                    mag.at<uchar>(i, j) > mag.at<uchar>(i - 1, j + 1)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            }
            if ((-112.5 <= angolo) && (angolo < -67.5) || (67.5 <= angolo) && (angolo < 112.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i + 1, j - 1) &&
                    mag.at<uchar>(i, j) > mag.at<uchar>(i - 1, j + 1)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            }
            if ((-157.5 <= angolo) && (angolo < -112.5) || (22.5 <= angolo) && (angolo < 67.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i + 1, j + 1) &&
                    mag.at<uchar>(i, j) > mag.at<uchar>(i - 1, j - 1)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            }
        }
    }
}

void Canny(Mat &src, Mat &dst, int lth, int hth, int ksize) {
    Mat tmp = src.clone();
    copyMakeBorder(tmp, tmp, ksize / 2, ksize / 2, ksize / 2, ksize / 2, 0);
    cv::GaussianBlur(tmp, tmp, Size(ksize, ksize), 0, 0);
    Mat Gx, Gy;
    Sobel(tmp, Gx, CV_32FC1, 1, 0, ksize);
    Sobel(tmp, Gx, CV_32FC1, 0, 1, ksize);
    Mat Gx2, Gy2;
    pow(Gx, 2, Gx2);
    pow(Gy, 2, Gy2);
    Mat mag;
    sqrt(Gx2 + Gy2, mag);
    Mat orientation;
    normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8U);
    phase(Gx, Gy, orientation, true);
    Mat nms = Mat::zeros(tmp.rows, tmp.cols, CV_8U);
    NMS(mag, orientation, nms);
    isteresis_thresholding(nms, lth, hth, dst);
}

int main(int argc, char **argv) {
    const char *ImageName = argc > 2 ? argv[1] : "../immagini/a.jpeg";
    Mat m = imread(ImageName, IMREAD_COLOR);
    Canny(m, m, 40, 90, 3);
    imshow("canny", m);
    waitKey(0);

}