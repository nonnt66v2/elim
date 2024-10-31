#include <opencv4/opencv2/opencv.hpp>
#include <vector>
#include <iomanip>

using namespace cv;
using namespace std;

void printMatrix(const vector<vector<int>> &matrix) {
    for (const auto &row: matrix) {
        for (const auto &elem: row) {
            cout << setw(3) << elem;
        }
        cout << endl;
    }
}

void polarToCartesian(double rho, int theta, Point &p1, Point &p2, int alpha) {

    int x0 = rho * cos(theta);
    int y0 = rho * sin(theta);

    /*p1.x = cvRound(x0 + alpha * (-sin(theta)));
    p1.y = cvRound(y0 + alpha * (cos(theta)));
    p2.x = cvRound(x0 - alpha * (-sin(theta)));
    p2.y = cvRound(y0 - alpha * (cos(theta)));*/
    p1.x = x0+alpha;
    p1.y = y0+alpha;
    p2.x = -x0+alpha;
    p2.y = -y0+alpha;
}

void HoughLines(Mat &src, Mat &dst, int th, int ksize) {
    Mat edge;
    int ipotenusa = hypot(src.rows, src.cols);
    int paddingDim = ksize / 2;
    copyMakeBorder(edge, edge, paddingDim, paddingDim, paddingDim, paddingDim, 0);
    Mat gsbl;
    GaussianBlur(src, gsbl, Size(5, 5), 0, 0);
    Canny(gsbl, edge, 40, 150);
    /*imshow("canny", edge);
    waitKey(0);*/
//    Mat votes = Mat::zeros(ipotenusa, 360,CV_8UC1);
//    vector<vector<int>> votes (ipotenusa*2,vector<int>(180,0));
    Mat votes = Mat::zeros(ipotenusa * 2, 180, CV_8U);
    double rho;
    double theta;
    double pi = CV_PI / 180;
    for (int i = 0; i < edge.rows; i++) {         //y
        for (int j = 0; j < edge.cols; j++) {    //x
            if (edge.at<uchar>(i, j) == 255) {
                for (theta = 0; theta < 180; theta++) {
                    rho = round(j * (cos(theta - 90)) + i * (sin(theta - 90))) + ipotenusa;
                    votes.at<uchar>(rho, theta)++;
                }
                cout << "\n";
            }
        }
    }
//    printMatrix(votes);
//    imshow("voti", votes);
//    waitKey(0);
    dst = src.clone();
    Point p1, p2;
    for (int i = 0; i < votes.rows; i++) {
        for (int j = 0; j < votes.cols; j++) {
            if (votes.at<uchar>(i, j) > th) {
                rho = i - ipotenusa;
                theta = j - 90;
//                theta*=pi;
                polarToCartesian(rho, theta, p1, p2, ipotenusa);
                line(dst, p1, p2, Scalar(0));
            }
        }
    }
}

int main(int argc, char **argv) {
    const char *Imagename = argc > 1 ? argv[1] : "../immagini/a.jpeg";
    Mat src = imread(samples::findFile(Imagename), IMREAD_COLOR);
    imshow("start", src);
    waitKey(0);
    Mat dst;
    int th = 87;
    /*while (th++ < 255) {
        HoughLines(src, dst, th, 3);
        cout<<th<<endl;
        imshow("harris", dst);
        waitKey(300);
    }*/
    HoughLines(src, dst, th, 3);
    cout<<th<<endl;
    imshow("harris", dst);
    waitKey(0);
}
