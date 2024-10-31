#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

const char *source_window = "Harris";

void myHarris(Mat &src, Mat &dst, int ksize, float k, int th) {
//    copyMakeBorder(src, src, ksize / 2, ksize / 2, ksize / 2, ksize / 2, BORDER_DEFAULT, Scalar(0));
    Mat Dx, Dy;
    Sobel(src, Dx, CV_32FC1, 1, 0, ksize);
    Sobel(src, Dy, CV_32FC1, 0, 1, ksize);

    Mat Dx2, Dy2, Dxy;
    pow(Dx, 2.0, Dx2);
    pow(Dy, 2.0, Dy2);
    multiply(Dx, Dy, Dxy);

    Mat Dx2g, Dy2g, Dxyg;
    GaussianBlur(Dx2, Dx2g, Size(7, 7), 2.0, 0);
    GaussianBlur(Dy2, Dy2g, Size(7, 7), 0.0, 2.0);
    GaussianBlur(Dxy, Dxyg, Size(7, 7), 2.0, 2.0);

    Mat x2y2, xy, mtrace, R;
    //diagonale principale
    multiply(Dx2g, Dy2g, x2y2);
    //diagonale secondaria
    multiply(Dxyg, Dxyg, xy);
    //traccia al 2
    pow((Dx2g + Dy2g), 2, mtrace);
    R = (x2y2 - xy) - k * mtrace;
    normalize(R, R, 0, 255, NORM_MINMAX, CV_8UC1);
    for (int i = 1; i < R.rows - 1; i++) {
        for (int j = 1; j < R.cols - 1; j++) {
            if (R.at<uchar>(i, j) > th) {
                circle(dst, Point(j, i), 5, Scalar(0), 5, 8, 0);
            }
        }
    }

}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "../immagini/img.png";
    Mat m = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
    normalize(m, m, 0, 255, NORM_MINMAX, CV_8UC1);
//    resize(m,m,Size(400,250));
    Mat m2 = m.clone();
    float i = 0.02;
    int th = 100;
    /*while(i<1 && th > 0) {
//        i+=0.01;
        std::cout<<th<<std::endl;
        th--;
        myHarris(m, m2, 3, i, th);
        imshow("Harris", m2);
        waitKey(100);
    }*/
//    Parametri leaf (leaf.png)
/*    myHarris(m, m2, 3, 0.02, 36);
    namedWindow(source_window);
    imshow("Harris", m2);
    imshow("Originale", m);*/
//    Parametri Denise (img.png)
    myHarris(m, m2, 3, 0.022, 9);
    namedWindow(source_window);
    imshow("Harris", m2);
    imshow("Originale", m);
    waitKey(0);

    return 0;
}
