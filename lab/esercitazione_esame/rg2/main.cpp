#include <opencv4/opencv2/opencv.hpp>
#include <stack>

using namespace std;
using namespace cv;
Point shiftPoint2D[8]{
        Point(-1, -1), Point(-1, 0), Point(-1, 1),
        Point(0, -1), Point(0, 1),
        Point(1, -1), Point(1, 0), Point(1, 1)
};
double min_area_region = 0.01;
int max_area_region = 100;

void grow(Mat &src, Mat &dst, Mat &mask, Point seed, int th) {
    stack<Point> stack;
    stack.push(seed);

    Point center;
    Point ePoint;
    while (!stack.empty()) {
        center = stack.top();
        mask.at<uchar>(center) = 1;
        stack.pop();
        for (int i = 0; i < 8; i++) {
            ePoint = center + shiftPoint2D[i];
            if (ePoint.x < 0 || ePoint.x > src.rows || ePoint.y < 0 || ePoint.y > src.cols) {
                continue;
            } else {
                //distanza colore
                int delta = int(pow(src.at<Vec3b>(center)[0] - src.at<Vec3b>(ePoint)[0], 2) +
                            pow(src.at<Vec3b>(center)[1] - src.at<Vec3b>(ePoint)[1], 2) +
                            pow(src.at<Vec3b>(center)[2] - src.at<Vec3b>(ePoint)[2], 2));
                if (dst.at<uchar>(ePoint) == 0 &&
                    mask.at<uchar>(ePoint) == 0 &&
                    delta < th) {
                    mask.at<uchar>(ePoint) = 1;
                    stack.push(ePoint);
                }
            }
        }

    }

}

int main(int argc, char **argv) {
    const char *Imagename = argc > 1 ? argv[1] : "../immagini/otsu2.png";
    Mat src = imread(samples::findFile(Imagename), IMREAD_COLOR);
    int exp = log(min(src.rows,src.cols))/log(2);
    int dim = pow(2,exp);
    resize(src,src,Size(dim,dim));
    Mat dst = Mat::zeros(src.rows, src.cols, src.type());
    Mat mask = Mat::zeros(src.rows, src.cols, src.type());
    int th = 200;
    int padding =1;
    vector<Mat> masks;
    min_area_region=min_area_region*src.cols*src.rows;
    for(int x=0;x<src.rows;x++){
        for(int y=0;y<src.cols;y++){
            if(dst.at<uchar>(Point(x,y)) == 0){
                grow(src,dst,mask,Point(x,y),th);
                double maskSum = sum(mask).val[0];
                if(maskSum > min_area_region){
                    dst += mask*padding;
                    masks.push_back(mask.clone()*255);
                    if(++padding > max_area_region){
                        cout<<"area troppo grande";
                        return -1;
                    }
                }
                else{
                    dst+=mask*255;
                }
            }
            mask-=mask;
        }
    }
    //rg
    for(const auto& x : masks) {
        imshow("rg", x);
        waitKey(0);
    }

}
