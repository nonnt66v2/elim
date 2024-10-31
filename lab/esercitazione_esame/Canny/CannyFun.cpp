#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int kernel_size = 3;

void thresholding(Mat &img,Mat &out,int lth, int hth){
  for(int i=1; i<img.rows-1; i++){
    for(int j=1; j<img.cols-1; j++){
    	if(img.at<uchar>(i,j) > hth){
          out.at<uchar>(i,j) = 255;
        	for(int u=-1; u<=1; u++){
        		for(int v=-1; v<=1; v++){
            		if(img.at<uchar>(i+u, j+v) > lth && img.at<uchar>(i+u, j+v) < hth)
              			out.at<uchar>(i+u,j+v) = 255;
      			}
      		}
      	}
    }
  }
}

static void nonMaxSuppression(Mat &mag, Mat &orientations,Mat &nms){

  for(int i = 1; i < mag.rows-1; i++){
        for(int j = 1; j < mag.cols-1; j++){
            float angle = orientations.at<float>(i,j);
            angle = angle > 180 ? angle - 360 : angle;
            
            if( ((-22.5 < angle) && (angle <= 22.5) ) || ((-157.5 > angle) && (angle >= 157.5) )){
                if(mag.at<uchar>(i,j) >= mag.at<uchar>(i,j-1) && mag.at<uchar>(i,j) >= mag.at<uchar>(i,j+1) )
                  nms.at<uchar>(i,j) = mag.at<uchar>(i,j);
            }
            else if( ((-67.5 < angle) && (angle <= -22.5) ) || ((112.5 < angle) && (angle <= 157.5) )){
                if(mag.at<uchar>(i,j) >= mag.at<uchar>(i+1,j-1) && mag.at<uchar>(i,j) >= mag.at<uchar>(i-1,j+1) )
                  nms.at<uchar>(i,j) = mag.at<uchar>(i,j);
            }
            else if( ((-112.5 < angle) && (angle <= -67.5) ) || ((67.5 < angle) && (angle <= 112.5) )){
                if(mag.at<uchar>(i,j) >= mag.at<uchar>(i-1,j) && mag.at<uchar>(i,j) >= mag.at<uchar>(i+1,j) )
                  nms.at<uchar>(i,j) = mag.at<uchar>(i,j);
            }
            else if( ((-157.5 < angle) && (angle <= -112.5) ) || ((22.5 < angle) && (angle <= 67.5) )){
                if(mag.at<uchar>(i,j) >= mag.at<uchar>(i-1,j-1) && mag.at<uchar>(i,j) >= mag.at<uchar>(i+1,j+1) )
                  nms.at<uchar>(i,j) = mag.at<uchar>(i,j);
            }
        }
    }
}

static void myCanny(Mat &src, Mat &output, int kernel_size){
  
  Mat Gauss;
  GaussianBlur(src,Gauss,Size(5,5),0,0);

  Mat Dx;
  Sobel(Gauss,Dx,CV_32FC1,1,0,kernel_size);
  Mat Dy;
  Sobel(Gauss,Dy,CV_32FC1,0,1,kernel_size);

  Mat mag,Dx2,Dy2;
  pow(Dx,2,Dx2);
  pow(Dy,2,Dy2);
  sqrt(Dx2+Dy2,mag);
  normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8U);

  Mat orientations;
  phase(Dx,Dy,orientations,true);

  Mat nms=Mat::zeros(mag.rows,mag.cols,CV_8U);
  nonMaxSuppression(mag,orientations,nms);
  imshow("nms",nms);
  waitKey(0);

  Mat out=Mat::zeros(mag.rows,mag.cols,CV_8U);
  thresholding(nms,out,40,90);

  output=out;
}


int main( int argc, char** argv )
{
  if( argc < 2){
    cout<<"usage: "<<argv[0]<<" image_name"<<endl;
        exit(0);
    }
  String imageName = argv[1];

  //Lettura immagine    
  Mat image;
  image = imread(imageName, IMREAD_GRAYSCALE );
  if( image.empty() ){
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
  }

  Mat output;
  myCanny(image,output,kernel_size);

  imshow("Canny",output);
  waitKey(0);
  return 0;
}