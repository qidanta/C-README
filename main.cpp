#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <glog/logging.h>
#include <iostream>
#include <vector>
#include <string>
#include "./rect/calculate.h"
#include "./rect/read.h"
#include "str/segmentation.h"

using namespace cv;
using namespace std;

void test_per() {
    vector<string> mps = read("/home/eric/CLionProjects/readme/README/compile-jpg.txt");
    for (int i = 0; i < mps.size(); ++i) {
        //"POLYGON((0 0,0 200,200 200,200 0,0 0))" pg contain rect
        //"POLYGON((200 200,200 400,400 400,400 200,200 200))" pg overlap rect
        // "POLYGON((0 0,0 400,400 400,400 0,0 0))" rect contain pg
        //per("POLYGON((0 0,0 200,200 200,200 0,0 0))",  mps[i])
        // "" can't calculate pg = rect
        cout << per("POLYGON((0 0,0 200,200 200,200 0,0 0))",  mps[i]);
    }
}

void test_split() {
    vector<string> v;
    string s = "a,b,c";
    SplitString(s, v, ",");
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i];
    }
    LOG(INFO) << "HELLO WORLD";
}

void test_read_img() {
    vector<Mat> imgs;
    Mat img;
    int length = 5;
    for (int i = 0; i < length; ++i) {
        img = imread("/home/eric/CLionProjects/readme/README/lena.jpg");
        imgs.push_back(img);
    }
    if (imgs[1].data) {
        namedWindow("Display Image", WINDOW_AUTOSIZE );
        imshow("Display Image", imgs[1]);
        LOG(INFO) << "success show index=1's img in imgs";
        waitKey(0);
    }
    imgs.clear();
    if(!imgs[1].data) {
        LOG(INFO) << "success clear";
    }
}


int main(int argc, char* argv[]) {
    FLAGS_log_dir = "/home/eric/CLionProjects/readme/log";
    google::InitGoogleLogging(argv[0]);
    //google::SetLogDestination(google::GLOG_INFO, "./log/log_info_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
    //test_per();
    //test_split();
    test_read_img();
    return 0;
}