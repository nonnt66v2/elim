#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int otsu_1soglia(vector <double> &istogramma) {
    const int L=256;
    int eta = 0;
    double p1 = 0.0f;
    double mk = 0.0f;
    double mg = 0.0f;
    double sigmaG = 0.0f;
    double sigmaB = 0.0f;
    double maxVar = 0.0f;
    for (int j = 0; j < L-1; j++) {
        mg += (j + 1) * istogramma[j];
    }
    for (int i = 0; i < L-1; i++) {
        p1 += istogramma[i];
        mk += (i+1)*istogramma[i];
//        sigmaG = pow((i + 1 - mg), 2) * istogramma[i];
        sigmaB = (mg * p1 - mk) / p1 * (1 - p1);
        if(sigmaB > maxVar){
            maxVar = sigmaB;
            eta = i;
        }
    }
    return eta;

}

int main(int argc, char **argv) {
    const char *Imagename = argc > 1 ? argv[1] : "../immagini/otsu2.png";
    Mat src = imread(samples::findFile(Imagename), IMREAD_COLOR);
    Mat dst;
    cvtColor(src, src, COLOR_RGB2BGR);
    cvtColor(src, src, COLOR_BGR2GRAY);
    Mat tmp = src.clone();
    GaussianBlur(src, tmp, Size(3, 3), 0, 0);
//    cvtColor(tmp, tmp, COLOR_RGB2BGR);
//    cvtColor(tmp, tmp, COLOR_BGR2GRAY);
    normalize(tmp, tmp, 0, 255, NORM_MINMAX);
    const int L = 256;
    vector<double> istogramma(256, 0.0f);
    for (int y = 0; y < tmp.rows; y++) {
        for (int x = 0; x < tmp.cols; x++) {
            istogramma[tmp.at<uchar>(y, x)]++;
        }
    }

    double ni = 0;
    for (int y = 0; y <= L - 1; y++) {
        istogramma[y] /= (tmp.cols * tmp.rows);
        ni += istogramma[y];
    }
    cout << ni << endl;
    imshow("blur",tmp);
    waitKey(0);
//    Canny(tmp,dst,otsu_1soglia(istogramma),255,3,false);
    threshold(tmp, dst, otsu_1soglia(istogramma), 255, THRESH_OTSU);
    imshow("otsu", dst);
    waitKey(0);


}
