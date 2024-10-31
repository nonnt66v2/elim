#include <opencv4/opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

#define L 256

vector<double> istogrammaNormalizzato(Mat &src) {
    vector<double> istogramma(256, 0.0f);
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            istogramma[src.at<uchar>(i, j)]++;
        }
    }
    for (int i = 0; i < L; i++) {
        istogramma[i] /= (src.rows * src.cols);
    }
    return istogramma;
}

vector<int> otsu_2soglie(vector<double> istogramma) {
    double mg = 0.0f;
    for (int i = 0; i < L; i++) {
        mg = (i + 1) * istogramma[i];
    }
    double p1, p2, p3;
    p1 = p2 = p3 = 0.0f;
    double m1, m2, m3;
    m1 = m2 = m3 = 0.0f;
    int etaB;
    int maxVar = 0;
    vector<int> soglia(2, 0);
    for (int i = 1; i < L - 2; i++) {
        p1 += istogramma[i];
        m1 += (i + 1) * istogramma[i];
        for (int j = i + 1; j < L - 1; j++) {
            p2 += istogramma[j];
            m2 += (j + 1) * istogramma[j];
            for (int k = j + 1; k < L; k++) {
                p3 += istogramma[k];
                m3 += (k + 1) * istogramma[k];
                etaB = (p1 * pow(m1 / p1 - mg, 2)) + (p2 * pow(m2 / p2 - mg, 2)) + (p3 * pow(m3 / p3 - mg, 2));
                if (etaB > maxVar) {
                    maxVar = etaB;
                    soglia[0] = i;
                    soglia[1] = j;
                }
            }
            p3 = m3 = 0.0f;
        }
        p2 = m2 = 0.0f;
    }
    return soglia;
}

void ist_threshold(Mat &src, Mat &dst, vector<int> soglia) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (src.at<uchar>(i, j) < soglia[0]) {
                dst.at<uchar>(i, j) = 0;
            } else if (src.at<uchar>(i, j) > soglia[0] && src.at<uchar>(i, j) < soglia[1])
                dst.at<uchar>(i, j) = 127;
            else {
                dst.at<uchar>(i, j) = 255;
            }
        }
    }
}

int main(int argc, char **argv) {
    const char *Imagename = argc > 1 ? argv[1] : "../immagini/otsu2.png";
    Mat src = imread(samples::findFile(Imagename), IMREAD_COLOR);
    cvtColor(src, src, COLOR_RGB2BGR);
    cvtColor(src, src, COLOR_BGR2GRAY);
    GaussianBlur(src, src, Size(9, 9), 0, 0);
    Mat dst = src.clone();
    vector<double> istogramma = istogrammaNormalizzato(src);
    vector<int> soglia(2, 0);
    soglia = otsu_2soglie(istogramma);
    cout << soglia[0] << " " << soglia[1];
    ist_threshold(src, dst, soglia);
    imshow("otsu2", dst);
    waitKey(0);
    return 0;
}