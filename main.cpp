#include "mainwindow.h"

#include <QApplication>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // opencv测试
//    string image_path = "C:\\Users\\Lassi\\Desktop\\rgbtohs\\error_map_picture\\ARAD_1K_0901\\ARAD_1K_0901.jpg";
//    Mat color_img;
//    color_img = imread(image_path);
//    imshow("test", color_img);

//    VideoCapture cap("D:\\project\\project_codes\\HW_target\\test.avi");
//    bool sign;
//    Mat img;

//    if (!cap.isOpened())
//    {
//        qDebug() << "The video is not exit.";
//    }

//    sign = cap.read(img);
//    qDebug() << sign;


    MainWindow w;
    w.show();
    return a.exec();
}
