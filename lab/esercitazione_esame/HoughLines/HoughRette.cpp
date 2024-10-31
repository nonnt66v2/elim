#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;


int main( int argc, char** argv ){
  Mat src = imread( argv[1], IMREAD_GRAYSCALE );

  if(src.empty()) {
    exit(-1);
  }

  GaussianBlur(src, src, Size(5,5), 0, 0);
    imshow("blur",src);
    waitKey(0);
  Mat edgeCanny;
  Canny(src, edgeCanny, 90, 160, 3);
  imshow("output",edgeCanny);
  waitKey(0);

  int dist = hypot(src.rows, src.cols);
  cout<<"ipotenusa: "<<dist<<endl;
  Mat votes = Mat::zeros(dist*2,180,CV_8U);
  double rho, theta;
  for(int x=0; x<edgeCanny.rows; x++){
    for(int y=0; y<edgeCanny.cols; y++){
      if(edgeCanny.at<uchar>(x,y) == 255){
        for(theta=0; theta<180; theta++){      
          rho = dist+y*cos((theta-90)*CV_PI/180) + x*sin((theta-90)*CV_PI/180);
          votes.at<uchar>(rho, theta)++;
        }
      }     
    }
  }
    imshow("voti",votes);
    waitKey(0);

  for(int r=0; r<votes.rows; r++){
      for(int t=0; t<votes.cols; t++){
        if(votes.at<uchar>(r,t) >= 90){
          theta = (t-90) * CV_PI/180;
          int x = (r-dist) * cos(theta);
          int y = (r-dist) * sin(theta);
          double sin_t=sin(theta);
          double cos_t=cos(theta);
          Point pt1( cvRound(x + dist*(-sin_t)), cvRound(y + dist*cos_t) );
          Point pt2( cvRound(x - dist*(-sin_t)), cvRound(y - dist*cos_t) );
          line(src, pt1, pt2, Scalar(255), 1, 0);
        }
      }
    }

  imshow("output",src);
  waitKey(0);

  return 0;
}