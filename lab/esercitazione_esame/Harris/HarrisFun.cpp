#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void myHarris(Mat &src, Mat &output,int kernel_size,float k,int thresh){
  

  Mat Dx, Dy;
  Sobel(src, Dx, CV_32FC1 , 1, 0, kernel_size, BORDER_DEFAULT);
  Sobel(src, Dy, CV_32FC1 , 0, 1, kernel_size, BORDER_DEFAULT);

  Mat Dx2, Dy2, Dxy;
  pow(Dx,2.0,Dx2);
  pow(Dy,2.0,Dy2);
  multiply(Dx,Dy,Dxy);

  Mat Dx2g, Dy2g, Dxyg;
  GaussianBlur(Dx2,Dx2g,Size(7,7),2.0,0.0,BORDER_DEFAULT);
  GaussianBlur(Dy2,Dy2g,Size(7,7),0.0,2.0,BORDER_DEFAULT);
  GaussianBlur(Dxy,Dxyg,Size(7,7),2.0,2.0,BORDER_DEFAULT);
  
  /*for(int i=0;i<src.rows;i++)
    for(int j=0;j<src.cols;j++)
      cout<<Dx2g.at<float>(i,j)<<"-"<<Dy2g.at<float>(i,j)<<endl;*/

  Mat x2y2, xy, mtrace, R;
  multiply(Dx2g,Dy2g,x2y2);
  multiply(Dxyg,Dxyg,xy);
  pow((Dx2g + Dy2g),2.0,mtrace);
  R = (x2y2 - xy) - k * mtrace;
  

  normalize( R, R, 0, 255, NORM_MINMAX, CV_32FC1);
  
  output=src.clone();

  for(int i=0;i<src.rows;i++)
    for(int j=0;j<src.cols;j++)
      if((int)R.at<float>(i,j) > thresh)
        circle(output, Point(j,i), 5, Scalar(255), 2, 8, 0);
}

int main( int argc, char** argv )
{

  String imageName = argc >= 2 ? argv[1] : "../immagini/b.png";

  //Lettura immagine    
  Mat image;
  image = imread(imageName, IMREAD_GRAYSCALE );
  if( image.empty() ){
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
  }

  Mat output;
  resize(image,image,Size(image.cols/2,image.rows/2));
  myHarris(image,output,3,0.04,100);

  imshow("Harris",output);
  waitKey(0);
  return 0;
}