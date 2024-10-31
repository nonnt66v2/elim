#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void kmeans(Mat &src, Mat &dst, int k) {
    srand(time(NULL));
    vector<Vec3b> c(k, 0);
    for (int x = 0; x < k; x++) {
        int randR = rand() % src.rows;
        int randC = rand() % src.cols;
        c[x] = src.at<uchar>(randR, randC);
    }
    double epsilon = 0.01f;
    bool centroCambiato = true;
    int maxIterazioni = 50;
    int it = 0;
    vector<Vec3b> nuovaMedia(k, 0);
    vector<Vec3b> vecchiaMedia(k, 0);
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
//                    dist[i] = abs(c[i] - src.at<uchar>(x, y));
                        dist[i] = sqrt(pow(c[i].val[0] - src.at<Vec3b>(x,y)[0],2) +
                                               pow(c[i].val[1] - src.at<Vec3b>(x,y)[1],2) +
                                               pow(c[i].val[2] - src.at<Vec3b>(x,y)[2],2) );

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
                nuovaMedia[x].val[0] += src.at<Vec3b>(cx, cy)[0];
                nuovaMedia[x].val[1] += src.at<Vec3b>(cx, cy)[1];
                nuovaMedia[x].val[2] += src.at<Vec3b>(cx, cy)[2];
            }
            nuovaMedia[x] /= csize;
            c[x] = nuovaMedia[x];
        }
        double val = 0.0f;
        for (int x = 0; x < k; x++) {
            for(int i=0;i<3;i++){
                val+= nuovaMedia[x].val[i] - vecchiaMedia[x].val[i];
            }
            val/=3;
            if(abs(val) <=epsilon){
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
            dst.at<Vec3b>(cx, cy) = c[x];
        }
    }
}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "../immagini/leaf.png";
    Mat src = imread(samples::findFile(imageName), IMREAD_COLOR);
    Mat dst;
    //resize(src,src,Size(src.cols*2,src.rows*2),0,0);
    int soglia=1;
    kmeans(src, dst, soglia);
    imshow("kmeans", dst);
    waitKey(10000);
}
//
// Created by nonnt66 on 15/07/24.
//
