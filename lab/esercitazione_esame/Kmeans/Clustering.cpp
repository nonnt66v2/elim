#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void Kmeans(Mat &src,int k){

    Mat data;
    src.convertTo(data,CV_32F);
    data = data.reshape(1,data.total());

    Mat labels, centers;
    kmeans(data, k, labels, TermCriteria(TermCriteria::MAX_ITER, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);

    centers = centers.reshape(3,centers.rows);
    data = data.reshape(3,data.rows);

    Vec3f *p = data.ptr<Vec3f>();
    for (size_t i=0; i<data.rows; i++) {
       int center_id = labels.at<int>(i);
       p[i] = centers.at<Vec3f>(center_id);
    }

    src = data.reshape(3, src.rows);
    src.convertTo(src, CV_8U);
}

int main( int argc, char** argv ){

    Mat src = imread( argv[1]);
    
    if(src.empty())
        exit(-1);

    Mat dst;
    pyrMeanShiftFiltering(src,dst,20,40,0);

    Mat kdst=src.clone();
    Kmeans(kdst,stoi(argv[2]));

    imshow("Image",src);
    imshow("Segmented meanshift", dst);
    imshow("Segmented k-means", kdst);
    waitKey(0);

    return 0;
}