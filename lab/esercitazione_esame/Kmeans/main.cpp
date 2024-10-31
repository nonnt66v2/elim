#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void kmeans(Mat &src, Mat &dst, int k) {
    srand(time(NULL));
    vector<uchar> c(k, 0);
    for (int x = 0; x < k; x++) {
        int randR = rand() % src.rows;
        int randC = rand() % src.cols;
        c[x] = src.at<uchar>(randR, randC);
    }
    double epsilon = 0.01f;
    bool centroCambiato = true;
    int maxIterazioni = 50;
    int it = 0;
    vector<double> nuovaMedia(k, 0);
    vector<double> vecchiaMedia(k, 0);
    vector<vector<Point>> cluster(k);
    vector<uchar> dist(k, 0);
    int minDistDalCentro;

    while (centroCambiato && it++ < maxIterazioni) {
        centroCambiato = false;
        for (int x = 0; x < k; x++) cluster[x].clear();
        for (int x = 0; x < k; x++) vecchiaMedia[x] = nuovaMedia[x];
        for (int x = 0; x < src.rows; x++) {
            for (int y = 0; y < src.cols; y++) {
                for (int i = 0; i < k; i++) {
                    dist[i] = abs(c[i] - src.at<uchar>(x, y));
                }
                minDistDalCentro = min_element(dist.begin(), dist.end()) - dist.begin();
                cluster[minDistDalCentro].push_back(Point(x, y));
            }
        }
        for (int x = 0; x < k; x++) {
            int csize = static_cast<int>(cluster.size());
            for (int i = 0; i < csize; i++) {
                int cx = cluster[x][i].x;
                int cy = cluster[x][i].y;
                nuovaMedia[x] += src.at<uchar>(cx, cy);
            }
            nuovaMedia[x] /= csize;
            c[x] = uchar(nuovaMedia[x]);
        }
        for (int x = 0; x < k; x++) {
            if (!(abs(nuovaMedia[x] - vecchiaMedia[x]) <= epsilon)) {
                centroCambiato = true;
            }
        }
    }
    dst = src.clone();
    for (int x = 0; x < k; x++) {
        int csize = static_cast<int>(cluster.size());
        for (int i = 0; i < csize; i++) {
            int cx = cluster[x][i].x;
            int cy = cluster[x][i].y;
            dst.at<uchar>(cx, cy) = c[x];
        }
    }
}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "../immagini/leaf.png";
    Mat src = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
    Mat dst;
    resize(src,src,Size(src.cols*2,src.rows*2),0,0);
    int soglia=1;
    while(soglia++ < 10) {
        cout<<soglia<<"\n";
        kmeans(src, dst, soglia);
        imshow("kmeans", dst);
        waitKey(1000);
    }
}
