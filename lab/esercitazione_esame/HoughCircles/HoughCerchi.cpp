#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;


int main( int argc, char** argv ){
  Mat src = imread( argv[1], IMREAD_GRAYSCALE );

  if(src.empty()) {
    exit(-1);
  }

  GaussianBlur(src, src, Size(9,9), 0, 0);

  Mat edgeCanny;
  Canny(src, edgeCanny, 150, 250, 3);
  imshow("Canny",edgeCanny);


  int r_min=60;
  int r_max=90;
  int sizes[]={edgeCanny.rows,edgeCanny.cols,r_max-r_min+1};
  Mat votes = Mat(3,sizes,CV_8U,Scalar(0));

  for(int x=0; x<edgeCanny.rows; x++){
    for(int y=0; y<edgeCanny.cols; y++){
      if(edgeCanny.at<uchar>(x,y) == 255){
        for(int r=r_min;r<=r_max;r++){      
          for(int theta=0;theta<360;theta++){
            int a = y - r*cos(theta*M_PI/180);
            int b = x - r*sin(theta*M_PI/180);
            if(a >= 0 && a < edgeCanny.cols && b >= 0 && b < edgeCanny.rows)
              votes.at<uchar>(b,a,r-r_min)++;
          }
        }
      }     
    }
  }


for(int r=r_min; r<r_max; r++){
    for(int b=0;b<edgeCanny.rows;b++){
      for(int a=0;a<edgeCanny.cols;a++){
        if(votes.at<uchar>(b,a,r-r_min)>90){
          circle(src, Point(a,b), 1, Scalar(0), 2, 8, 0);
          circle(src, Point(a,b), r, Scalar(0), 2, 8, 0);
        }
      }
    }
  }

  imshow("output",src);
  waitKey(0);

  return 0;
}