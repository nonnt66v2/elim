#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int tsize;
int smthresh;

class TNode {
public:
    Rect region;
    TNode *UL, *UR, *LL, *LR;
    vector<TNode *> merged;
    vector<bool> mergedB = vector<bool>(4, false);
    double stddev, mean;

    TNode(Rect R) {
        region = R;
        UL = UR = LL = LR = nullptr;
    }

    void addRegion(TNode *R) { merged.push_back(R); }

    void setMergedB(int i) { mergedB[i] = true; }

};

TNode *split(Mat &src, Rect R) {
    TNode *root = new TNode(R);
    Scalar mean, stddev;
    meanStdDev(src(R), mean, stddev);
    root->mean = mean[0];
    root->stddev = stddev[0];
    if (R.width > tsize && root->stddev > smthresh) {
        Rect ul(R.x, R.y, R.height / 2, R.width / 2);
        root->UL = split(src, ul);
        Rect ur(R.x, R.y + R.height / 2, R.height / 2, R.width / 2);
        root->UR = split(src, ur);
        Rect ll(R.x + R.width / 2, R.y, R.height / 2, R.width / 2);
        root->LL = split(src, ll);
        Rect lr(R.x + R.width / 2, R.y + R.height / 2, R.height / 2, R.width / 2);
        root->LR = split(src, lr);
    }
    rectangle(src, R, Scalar(0));
    return root;
}

void merge(TNode *root) {
    if (root->region.width > tsize && root->stddev > smthresh) {
        if (root->UL->stddev <= smthresh && root->UR->stddev <= smthresh) {
            root->addRegion(root->UL);
            root->addRegion(root->UR);
            root->setMergedB(0);
            root->setMergedB(1);
            if (root->LL->stddev <= smthresh && root->LR->stddev <= smthresh) {
                root->addRegion(root->LL);
                root->addRegion(root->LR);
                root->setMergedB(3);
                root->setMergedB(2);
            } else {
                merge(root->LR);
                merge(root->LL);
            }
        }
        if (root->UR->stddev <= smthresh && root->LR->stddev <= smthresh) {
            root->addRegion(root->UR);
            root->addRegion(root->LR);
            root->setMergedB(3);
            root->setMergedB(1);
            if (root->UL->stddev <= smthresh && root->LL->stddev <= smthresh) {
                root->addRegion(root->UL);
                root->addRegion(root->LL);
                root->setMergedB(2);
                root->setMergedB(0);
            } else {
                merge(root->UL);
                merge(root->LL);
            }
        }
        if (root->LL->stddev <= smthresh && root->LR->stddev <= smthresh) {
            root->addRegion(root->LL);
            root->addRegion(root->LR);
            root->setMergedB(2);
            root->setMergedB(3);
            if (root->UL->stddev <= smthresh && root->UR->stddev <= smthresh) {
                root->addRegion(root->UL);
                root->addRegion(root->LL);
                root->setMergedB(0);
                root->setMergedB(1);
            } else {
                merge(root->UL);
                merge(root->UR);
            }
        }
        if (root->UL->stddev <= smthresh && root->LL->stddev <= smthresh) {
            root->addRegion(root->UL);
            root->addRegion(root->LL);
            root->setMergedB(0);
            root->setMergedB(3);
            if (root->UR->stddev <= smthresh && root->LR->stddev <= smthresh) {
                root->addRegion(root->UR);
                root->addRegion(root->LR);
                root->setMergedB(1);
                root->setMergedB(2);
            } else {
                merge(root->UL);
                merge(root->LL);
            }
        } else {
            merge(root->UL);
            merge(root->LL);
            merge(root->UR);
            merge(root->LR);
        }
    } else {
        root->addRegion(root);
        for (int i = 0; i < 4; i++) {
            root->setMergedB(i);
        }
    }
}

void segment(TNode *root, Mat &src) {
    vector<TNode *> tmp = root->merged;
    if (!tmp.size()) {
        segment(root->UL, src);
        segment(root->LL, src);
        segment(root->UR, src);
        segment(root->LR, src);
    } else {
        double val = 0;
        for (auto x: tmp) {
            val += x->mean;
        }
        val /= tmp.size();
        for (auto x: tmp) {
            src(x->region) = (int) val;
        }
        if (tmp.size() > 1) {
            if (!root->merged[0]) {
                segment(root->UL, src);
            }
            if (!root->merged[1]) {
                segment(root->UR, src);
            }
            if (!root->merged[2]) {
                segment(root->LR, src);
            }
            if (!root->merged[3]) {
                segment(root->LL, src);
            }

        }
    }
}

void drawMerged(TNode *root, Mat &src) {
    vector<TNode *> tmp = root->merged;
    if (!tmp.size()) {
        drawMerged(root->UL, src);
        drawMerged(root->UR, src);
        drawMerged(root->LR, src);
        drawMerged(root->LL, src);
    } else if (tmp.size() == 1) {
        rectangle(src, tmp[0]->region, Scalar(0));
    } else {
        if (root->mergedB[0] && root->mergedB[1] || root->mergedB[2] && root->mergedB[3]) {
            rectangle(src, Rect(tmp[0]->region.x, tmp[0]->region.y, tmp[0]->region.height, tmp[0]->region.width * 2),
                      Scalar(0));
        }
        if (root->mergedB[0] && root->mergedB[3] || root->mergedB[1] && root->mergedB[2]) {
            rectangle(src, Rect(tmp[0]->region.x, tmp[0]->region.y, tmp[0]->region.height * 2, tmp[0]->region.width),
                      Scalar(0));
        }
        if (!root->mergedB[0]) {
            drawMerged(root->UL, src);
        }
        if (!root->mergedB[1]) {
            drawMerged(root->UR, src);
        }
        if (!root->mergedB[2]) {
            drawMerged(root->LR, src);
        }
        if (!root->mergedB[3]) {
            drawMerged(root->LL, src);
        }
    }
}

int main(int argc, char **argv) {
    const char *imageName = argc >= 4 ? argv[1] : "../immagini/leaf.png";
    tsize = atoi(argv[2]);
    smthresh = atoi(argv[3]);
    Mat src = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
    int exponent = log(min(src.rows, src.cols)) / log(2);
    int s = pow(2.0, double(exponent));
    Rect square = Rect(0, 0, s, s);
    src = src(square).clone();
    GaussianBlur(src, src, Size(3, 3), 0, 0);
    TNode *root = split(src, Rect(0, 0, src.rows, src.cols));
    merge(root);
    Mat srcMer = src.clone();
    Mat srcSeg = src.clone();
    drawMerged(root, srcMer);
    segment(root, srcSeg);
    imshow("quad tree", src);
    imshow("merged", srcMer);
    imshow("segment", srcSeg);
    waitKey(0);
}
