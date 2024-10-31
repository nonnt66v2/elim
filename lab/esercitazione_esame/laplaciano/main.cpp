#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

Mat laplaciano(Mat src,int ddepth,int size) {
    Mat dst(src.rows,src.cols,src.type());
    float data[9];
    //Laplaciano 90
    switch(size){
        case 1: {
            float data90[] = {0.0,1.0,0.0,
                             1.0,-4.0,1.0,
                             0.0,1.0,0.0};
            std::copy(data90,data90+sizeof(data90)/sizeof(data90[0]),data);
            break;
        }
        case 2: {
            float data45[] = {1.0,1.0,1.0,
                             1.0,-8.0,1.0,
                             1.0,1.0,1.0};
            std::copy(data45,data45+sizeof(data45)/sizeof(data45[0]),data);
            break;
        }

    }
    Mat kernel(3,3,CV_32F,data);
    filter2D(src,dst,ddepth,kernel);
    return dst;
}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "a.jpeg";
    cv::Mat m = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
    Mat m2(m.rows,m.cols,m.type());
    int dimKernel;
    std::cout << "inserisci la dimensione (dispari) del kernel: ";
    std::cin >> dimKernel;
    copyMakeBorder(m,m,dimKernel/2,dimKernel/2,dimKernel/2,dimKernel/2,BORDER_DEFAULT,Scalar(0));
    Mat kernel = Mat::ones(dimKernel,dimKernel,CV_32F)/(float)(dimKernel*dimKernel);
    // GaussianBlur(m,m2,Size(kernel.rows,kernel.cols),0,0,BORDER_DEFAULT);
    // imshow("median Blur", m2);
    // // threshold(m2,m2,200,255,ADAPTIVE_THRESH_MEAN_C);
    // adaptiveThreshold(m2,m2,255,BORDER_REPLICATE,THRESH_BINARY,dimKernel,0);
    // imshow("threshold", m2);
    // waitKey(0);
    Laplacian(m,m2,CV_8UC1,1);
    imshow("Laplacian", m2);
    Mat m3 = laplaciano(m,CV_8UC1,1);
    imshow("Laplaciano mio", m3);
    waitKey(0);
    return 0;
}
