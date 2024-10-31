#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

void thresholding(Mat &nms, Mat &dst, int lth, int hth) {
    for (int i = 1; i < nms.rows - 1; i++) {
        for (int j = 1; j < nms.cols - 1; j++) {
            if (nms.at<uchar>(i, j) > hth) dst.at<uchar>(i, j) = 255;
            for (int u = -1; u <= 1; u++) {
                for (int v = -1; v <= 1; v++) {
                    if (nms.at<uchar>(i + u, j + v) > lth && nms.at<uchar>(i + u, j + v) < hth) {
                        dst.at<uchar>(i + u, j + v) = 255;
                    }
                }
            }
        }
    }
}

void NMS(Mat &mag, Mat &orientazione, Mat &nms) {
    for (int i = 1; i < mag.rows - 1; i++) {
        for (int j = 1; j < mag.cols - 1; j++) {
            uchar angolo = orientazione.at<uchar>(i, j);
            if (angolo > 180) angolo -= 360;
            if ((-22.5 < angolo) && (angolo <= 22.5) || (-157.5 < angolo) && (angolo <= 157.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i - 1, j) || mag.at<uchar>(i, j) > mag.at<uchar>(i + 1, j)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            } else if ((-67.5 < angolo) && (angolo <= -22.5) || (angolo < 112.5) && (angolo <= 157.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i + 1, j - 1) || mag.at<uchar>(i, j) > mag.at<
                        uchar>(i - 1, j + 1)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            } else if ((-112.5 < angolo) && (angolo <= -67.5) || (67.5 < angolo) && (angolo <= 112.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i, j - 1) || mag.at<uchar>(i, j) > mag.at<uchar>(i, j + 1)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            } else if ((-157.5 < angolo) && (angolo <= -112.5) || (22.5 < angolo) && (angolo <= 67.5)) {
                if (mag.at<uchar>(i, j) > mag.at<uchar>(i - 1, j - 1) || mag.at<uchar>(i, j) > mag.at<
                        uchar>(i + 1, j + 1)) {
                    nms.at<uchar>(i, j) = mag.at<uchar>(i, j);
                }
            }
        }
    }
}

void myCanny(Mat &src, Mat &dst, int ksize = 3) {
    copyMakeBorder(src, dst, ksize / 2, ksize / 2, ksize / 2, ksize / 2, BORDER_DEFAULT, Scalar(0));
    Mat matGauss;
    GaussianBlur(dst, matGauss, Size(ksize, ksize), 0, 0);
    Mat dx, dy;
    Sobel(matGauss, dx, CV_32FC1, 1, 0, ksize);
    Sobel(matGauss, dy, CV_32FC1, 0, 1, ksize);
    Mat d2x, d2y;
    pow(dx, 2, d2x);
    pow(dy, 2, d2y);
    Mat mag;
    sqrt(d2x + d2y, mag);
    normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8U);
    Mat orientazione;
    phase(dx, dx, orientazione, true);
    Mat nms = Mat::zeros(mag.rows, mag.cols, CV_8U);
    NMS(mag, orientazione, nms);
//    resize(nms, nms, Size(nms.cols / 2, nms.rows / 2), 0, 0);
    imshow("nms", nms);
    waitKey(0);
    Mat out = Mat::zeros(mag.rows, mag.cols, CV_8U);
    thresholding(nms, out, 40, 90);
    dst = out;

}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "../immagini/a.jpeg";
    Mat m = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
    Mat out;
    myCanny(m, out, 3);
    cv::resize(out, out, cv::Size(out.cols * 0.75,out.rows * 0.75), 0, 0);
    imshow("Canny", out);
    waitKey(0);
    return 0;
}
