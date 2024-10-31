#include <opencv4/opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;

double epsilon = 0.01f;

void kmeans(Mat &src, Mat &dst, int k) {

    srand(time(NULL));
    vector<int> c(k, 0);
    for (int i = 0; i < k; i++) {
        int x = rand() % src.rows;
        int y = rand() % src.cols;
        c[i] = src.at<uchar>(x, y);
    }

    bool is_changed = false;
    int max_iteration = 0;
    vector<vector<Point>> cluster(k);
    vector<double> newMean(k, 0);
    vector<double> oldMean(k, 0);
    int minDistInd = 0;
    vector<uchar> dist(k, 0);

    while (!is_changed && ++max_iteration < 50) {
        for (int i = 0; i < k; i++) cluster[i].clear();
        for (int i = 0; i < k; i++) newMean[i] = oldMean[i];

        for (int y = 0; y < src.rows; y++) {
            for (int x = 0; x < src.cols; x++) {
                for (int i = 0; i < k; i++) {
                    dist[i] = abs(c[i] - src.at<uchar>(y, x));
                }
                minDistInd = min_element(dist.begin(), dist.end()) - dist.begin();
                cluster[minDistInd].push_back(Point(y, x));
            }

            for (int i = 0; i < k; i++) {
                int csize = static_cast<int>(cluster[i].size());
                for (int j = 0; j < csize; j++) {
                    int cx = cluster[i][j].x;
                    int cy = cluster[i][j].y;
                    newMean[i] += src.at<uchar>(cx, cy);
                }
                newMean[i] /= csize;
                c[i] = uchar(newMean[i]);
            }

            for (int i = 0; i < k; i++) {
                if (!abs(newMean[i] - oldMean[i] <= epsilon)) {
                    is_changed = true;
                }
            }
        }

    }
    dst = src.clone();
    for (int i = 0; i < k; i++) {
        int csize = static_cast<int>(cluster[i].size());
        for (int j = 0; j < csize; j++) {
            int cx = cluster[i][j].x;
            int cy = cluster[i][j].y;
            dst.at<uchar>(cx, cy) = c[i];
        }
    }
}

int main() {
    Mat src = imread("../immagini/otsu2.png", IMREAD_GRAYSCALE);
    imshow("originale", src);
    waitKey(0);
    Mat dst;
    kmeans(src, dst, 3);
    imshow("kmeans", dst);
    waitKey(0);
}

