#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

Mat myLoG(Mat src,int ddepth, int ksize) {
    Mat GBMat, LoG;
    GaussianBlur(src,GBMat,Size(3,3),0,0);
    Laplacian(GBMat,LoG,ddepth,ksize);
    return LoG;
}
int main(int argc,char** argv) {
    const char* imageName = argc >= 2 ? argv[1] : "a.jpeg";
    Mat m = imread(samples::findFile(imageName),IMREAD_GRAYSCALE);
    int i=1;
    Mat m2 = m.clone();
    while (true) {
        if (i>30) i=1;
        m2 = myLoG(m,CV_8UC1,i+=2);
        resize(m2,m2,Size(m.cols/2,m.rows/2));
        imshow("myLog",m2);
        waitKey(50);
    }
    return 0;

}
