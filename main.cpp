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

void test_mutil_video() {
    VideoCapture cap;
    Mat frame;
    bool stop = false;
    int loops = 2, fps = 5;
    vector<Mat> frames;
    cap.open(0);
    while(!stop)
    {
        // wait for a new frame from camera and store it into 'frame'
        //cap.read(frame);
        for (int i = 0; i < fps; ++i) {
            cap >> frame;
            if (!frame.empty())
                frames.push_back(frame);
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frames[0]);
        frames.clear();
        LOG(INFO) << frames.size();
        if (waitKey(30)  == 27)
            stop = true;
    }
}

int test_local_camera() {
    VideoCapture cap("nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)I420, framerate=(fraction)24/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
    //VideoCapture cap("fakesrc ! videoconvert ! appsink");
    if (!cap.isOpened())
    {
        cout << "Failed to open camera." << endl;
        return -1;
    }

    for(;;)
    {
        Mat frame;
        cap >> frame;
        imshow("original", frame);
        //waitKey(1);
        if(waitKey(30) >= 0)
            break;
    }
    return 0;
    //cap.release();
}

int main(int argc, char* argv[]) {
    FLAGS_log_dir = "/home/eric/CLionProjects/readme/log";
    google::InitGoogleLogging(argv[0]);
    //google::SetLogDestination(google::GLOG_INFO, "./log/log_info_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
    //test_per();
    //test_split();
    //test_read_img();
    //test_mutil_video();
    test_local_camera();
    return 0;
}