#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <stack>

using namespace std;
using namespace cv;

const double min_region_area_factor = 0.01;
const uchar max_region_area = 100;
const int th = 200;
const Point shiftPoint2D[8] = {
        Point(-1, -1),
        Point(-1, 0),
        Point(-1, 1),
        Point(0, -1),
        Point(0, 1),
        Point(1, -1),
        Point(1, 0),
        Point(1, 1)
};

void grow(Mat &src, Mat &dst, Mat &mask, Point seed, int th) {
    stack<Point> point_stack;
    point_stack.push(seed);


    while (!point_stack.empty()) {
        Point center = point_stack.top();
        mask.at<uchar>(center) = 1;
        point_stack.pop();
        for (int i = 0; i < 8; i++) {
            cv::Point estimating_point = center + shiftPoint2D[i];
            if (estimating_point.x < 0
                || estimating_point.x > src.cols - 1
                || estimating_point.y < 0
                || estimating_point.y > src.rows - 1) {
                continue;
            } else {
                int delta = int(pow(src.at<Vec3b>(center)[0] - src.at<Vec3b>(estimating_point)[0], 2) +
                                pow(src.at<Vec3b>(center)[1] - src.at<Vec3b>(estimating_point)[1], 2) +
                                pow(src.at<Vec3b>(center)[2] - src.at<Vec3b>(estimating_point)[2], 2));
                if (dst.at<uchar>(estimating_point) == 0 &&
                    mask.at<uchar>(estimating_point) == 0 &&
                    delta < th) {
                    mask.at<uchar>(estimating_point) =1;
                    point_stack.push(estimating_point);

                }

            }

        }
    }

}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "../immagini/leaf.png";
    Mat src = imread(samples::findFile(imageName), IMREAD_COLOR);
    if (src.rows > 500 && src.cols > 500) {
        resize(src, src, Size(src.cols / 2, src.rows / 2), 0, 0);
    }
    int min_region_area = int(min_region_area_factor * src.cols * src.rows);  // small region will be ignored
    Mat dst = Mat::zeros(src.rows,src.cols,CV_8UC1);
    Mat mask = Mat::zeros(src.rows,src.cols,CV_8UC1);
    int padding = 1;
    for (int i = 0; i < src.rows - 1; i++) {
        for (int j = 0; j < src.cols - 1; j++) {
            if (dst.at<uchar>(Point(i, j)) == 0) {
                grow(src,dst,mask,Point(i,j),th);
                double mask_area = sum(mask).val[0];
                if(mask_area > min_region_area){
                    dst += mask*padding;
                    imshow("mask",mask*255);
                    waitKey();
                    if(++padding > max_region_area){
                        cout<<"area troppo grande\n";
                        return -1;
                    }
                }
                else{
                    dst += mask*255; //pixel ignorati
                }
            }
            mask-=mask;
        }
    }

}
