#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Otsu(vector<double> his) {
    double mediaCum = 0.0f;
    //media globale
    for (int i = 0; i < 256; i++)
        mediaCum += (i + 1) * his[i];
    double prob = 0.0f;
    double currMediaCum = 0.0f;
    double currVar = 0.0f;
    double maxVar = 0.0f;
    int thresh;
    for (int i = 0; i < 256; i++) {
        //eta^2->B = (mediaCum*prob-currMediaCum)^2 / (prob*(1-prob))
        /// se variazione corrente > max varaizione trovata = trovate soglia e maxVariazione
        //m1
        prob += his[i];
        //media corrente
        currMediaCum += (i + 1) * his[i];
        currVar = pow(mediaCum * prob - currMediaCum, 2) / (prob * (1 - prob));
        if (currVar > maxVar) {
            maxVar = currVar;
            thresh = i;
        }
    }
    return thresh;
}

vector<double> NormalizedHistogram(Mat img) {
    vector<double> his(256, 0.0f);
    for (int y = 0; y < img.rows; y++)
        for (int x = 0; x < img.cols; x++)
            his[img.at<uchar>(y, x)]++;
    for (int i = 0; i < 256; i++)
        his[i] /= img.rows * img.cols;
    return his;
}

vector<int> Otsu2(vector<double> his) {
    double mediaCum = 0.0f;
    for (int i = 0; i < 256; i++)
        mediaCum += (i + 1) * his[i];
    vector<double> prob(3, 0.0f);
    vector<double> currMediaCum(3, 0.0f);
    double currVar = 0.0f;
    double maxVar = 0.0f;
    vector<int> thresh(2, 0);
    for (int i = 0; i < 256 - 2; i++) {
        prob[0] += his[i];
        currMediaCum[0] += (i + 1) * his[i];
        for (int j = i + 1; j < 256 - 1; j++) {
            prob[1] += his[j];
            currMediaCum[1] += (j + 1) * his[j];
            for (int k = j + 1; k < 256; k++) {
                prob[2] += his[k];
                currMediaCum[2] += (k + 1) * his[k];
                currVar = 0.0f;
                for (int w = 0; w < 3; w++) {
                    currVar += prob[w] * pow(currMediaCum[w] / prob[w] - mediaCum, 2);
                }
                if (currVar > maxVar) {
                    maxVar = currVar;
                    thresh[0] = i;
                    thresh[1] = j;
                }
            }
            prob[2] = currMediaCum[2] = 0.0f;
        }
        prob[1] = currMediaCum[1] = 0.0f;
    }
    return thresh;
}


void MultipleThreshold(Mat img, Mat &out, vector<int> thresh) {
    out = Mat::zeros(img.size(), img.type());
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            if (img.at<uchar>(y, x) >= thresh[1])
                out.at<uchar>(y, x) = 255;
            else if (img.at<uchar>(y, x) >= thresh[0])
                out.at<uchar>(y, x) = 127;
        }
    }
}

int main(int argc, char **argv) {
    Mat img = imread(argv[1], IMREAD_GRAYSCALE);

    GaussianBlur(img, img, Size(3, 3), 0);
//    Laplacian(img,img,CV_8U,3,1);
    vector<double> hist = NormalizedHistogram(img);
    double y;
    for(auto x : hist){
        cout<<x<<endl;
    }
    Mat out;
    threshold(img, out, Otsu(hist), 255, THRESH_BINARY);
    imshow("img", out);
    waitKey(0);

    vector<int> thresh = Otsu2(hist);
    MultipleThreshold(img, out, thresh);
    imshow("img", out);
    waitKey(0);

    return 0;
}