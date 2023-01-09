#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
#define Height 480
#define Width 640
#define mxn 200

int main(){
    random_device rd;
    mt19937 gen(rd());
    for(int i = 0; i <= 10; i++){
        double p = double(i) / 10.0;

        binomial_distribution<> d(mxn, p);

        int hist[mxn + 1] = {};
        memset(hist, 0, sizeof(hist));
        VideoWriter video("bainomial" + to_string(i) + ".mp4", VideoWriter::fourcc('M', 'P', '4', 'V'), 60, Size(Width, Height));
        for(int n = 0; n < Height * 10; ++n){
            int ran = d(gen);
            ++hist[ran];
            if(n % 10 == 0){
                Mat img(Height, Width, CV_8UC3, Scalar(255, 255, 255));
                for(int i = 0; i <= mxn; i++){
                    int x = i * Width / (mxn + 1);
                    rectangle(img, Point(x, Height), Point(x + Width / (mxn + 1), Height - min(hist[i], Height)), Scalar(23, 17, 13), -1);
                }
                //加入橫坐標
                for(int i = 0; i <= mxn; i++){
                    if(i % 10 == 0){
                        int x = i * Width / (mxn + 1);
                        line(img, Point(x, Height), Point(x, Height - 10), Scalar(0, 0, 255), 1);
                        putText(img, to_string(i), Point(x, Height - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
                    }
                }
                video << img;
            }
        }
        for(int j = 0; j < 60; j++){
            Mat img(Height, Width, CV_8UC3, Scalar(255, 255, 255));
            for(int i = 0; i <= mxn; i++){
                int x = i * Width / (mxn + 1);
                rectangle(img, Point(x, Height), Point(x + Width / (mxn + 1), Height - min(hist[i], Height)), Scalar(23, 17, 13), -1);
            }
            for(int i = 0; i <= mxn; i++){
                if(i % 10 == 0){
                    int x = i * Width / (mxn + 1);
                    line(img, Point(x, Height), Point(x, Height - 10), Scalar(0, 0, 255), 1);
                    putText(img, to_string(i), Point(x, Height - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
                }
            }
            video << img;
        }
        for(int i = 1; i <= mxn; i++)
            cout << hist[i] << " ";
        cout << endl;
        video.release();
    }
    return 0;

}