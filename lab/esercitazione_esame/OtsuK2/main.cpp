#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using namespace std;

vector<int> Otsu2(vector<double> P_i) {
    double mediaCum = 0;
    for (int i = 0; i < 256; i++) {
        mediaCum = P_i[i] * (i + 1);
    }
    vector<double> mediaCumCurr(3, 0);
    vector<double> prob(3, 0);
    vector<int> soglia(2, 0);
    double currVar=0,maxVar=0;
    for (int i = 0; i < 256 - 2; i++) {
        mediaCumCurr[0] += (i + 1) * P_i[i];
        prob[0] += P_i[i];
        for (int j = i+1; j < 256 - 1; j++) {
            mediaCumCurr[1] += (j + 1) * P_i[j];
            prob[1] += P_i[j];
            currVar=0;
            for (int k = j+1; k < 256 ; k++) {
                mediaCumCurr[2] += (k + 1) * P_i[k];
                prob[2] += P_i[k];
                for(int l=0;l<3;l++){
                    currVar += prob[l] * pow((mediaCumCurr[l] / prob[l] - mediaCum),2);
                }
                if(currVar>maxVar){
                    soglia[0] = i;
                    soglia[1] = j;
                    maxVar = currVar;
                }
            }
            prob[2] = mediaCumCurr[2] = 0;
        }
        prob[1] = mediaCumCurr[1] = 0;
    }
    return soglia;
}

vector<double> normoIstogramma( Mat src) {
    vector<double> P_i(256, 0);
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            P_i[src.at<uchar>(y, x)]++;
        }
    }
    for (int i = 0; i < 256; i++) {
        P_i[i] /= src.rows * src.cols;
    }
    return P_i;
}

void multiSogliatura(Mat src, Mat &dst, vector<int> soglia) {
    for(int y=0;y<src.rows;y++){
        for(int x=0;x<src.cols;x++){
            if(src.at<uchar>(y,x) >= soglia[1]){
                dst.at<uchar>(y,x)  = 255;
            }
            else if(src.at<uchar>(y,x) >= soglia[0]){
                dst.at<uchar>(y,x)  = 127;
            }
        }
    }
}

int main(int argc, char **argv) {
    const char *imageName = argc >= 2 ? argv[1] : "../immagini/leaf.png";
    Mat src = imread(samples::findFile(imageName), IMREAD_GRAYSCALE);
    GaussianBlur(src,src,Size(3,3),0,0);
    Mat dst = Mat::zeros(src.rows,src.cols,src.type());
    vector<double> P_i = normoIstogramma(src);
    double y=0;
    for(auto x : P_i){
        y+=x;
    }
    vector<int> soglia = Otsu2(P_i);
    cout<<"[y] = "<<y<<" soglia 0: "<<soglia[0]<<" Soglia 1: "<<soglia[1]<<endl;
    multiSogliatura(src,dst, soglia);
    imshow("Otsu 2", dst);
    waitKey(0);


}
