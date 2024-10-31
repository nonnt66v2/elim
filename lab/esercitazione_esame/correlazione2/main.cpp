#include <stdio.h>
#include <opencv4/opencv2/opencv.hpp>


using namespace cv;

uchar tmpFunction(Mat pad,Mat mask,int offx,int offy) {
    float somma = 0;
    for (int k = 0; k < mask.rows; k++) {
        for (int l = 0; l < mask.cols; l++) {
            somma += pad.at<uchar>(k+offx, l+offy) * mask.at<float>(k, l);
        }
    }
    return somma;
}
Mat correlazione(Mat src, Mat kernel) {
    int dimPad = kernel.rows/2;
    Mat dst(src.rows, src.cols, src.type());
    Mat pad;
    copyMakeBorder(src, pad, dimPad, dimPad, dimPad, dimPad, BORDER_DEFAULT);
    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            dst.at<uchar>(i, j) = tmpFunction(pad,kernel,i,j);
        }
    }
    return dst;
}


int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "a.jpeg";
    Mat m = imread(samples::findFile(imageName),IMREAD_GRAYSCALE);
    Mat kernel = Mat::ones(3,3,CV_32F)/(float)(3*3);
    int i, j;
    std::cout << kernel << std::endl;
    std::cout << m.type() <<std::endl;
    std::cout << m.channels() <<std::endl;
    std::cout << m.depth() <<std::endl;
    // resize(m,m,Size(m.cols/2,m.rows/2));
    // normalize(m,m,0,255,NORM_MINMAX,IMREAD_GRAYSCALE);
    imshow("originale", m);
    Mat correlazioneImg = correlazione(m, kernel);
    imshow("correlazione", correlazioneImg);
    rotate(kernel,kernel,ROTATE_90_COUNTERCLOCKWISE);
    Mat convoluzioneImg = correlazione(m, kernel);
    imshow("convoluzione", convoluzioneImg);
    Mat matF2(m.rows,m.cols,m.type());
    filter2D(m,matF2,-1,kernel,Point(0,0),0,BORDER_DEFAULT);
    imshow("filter2D",matF2);

    // Mat matBlur(m.rows,m.cols,m.type());
    // blur(m,matBlur,Size(kernel.rows,kernel.cols),Point(-1,-1),BORDER_DEFAULT);
    // resize(matBlur,matBlur,Size(matBlur.rows/2,matBlur.cols/2));
    // imshow("blur",matBlur);
    // Mat matBoxFilter(m.rows,m.cols,m.type());
    // boxFilter(m,matBoxFilter,0,Size(kernel.rows,kernel.cols),Point(-1,-1),true,BORDER_DEFAULT);
    // ///altezza -> Righe
    // ///larghezza -> colonne
    // resize(matBoxFilter,matBoxFilter,Size(m.cols/2,m.rows/2));
    // imshow("boxFilter",matBoxFilter);

    waitKey(0);
    return 0;
}
