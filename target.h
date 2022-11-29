#ifndef TARGET_H
#define TARGET_H


#include "arr.h"
#include "arrs.h"

#include <QObject>

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <random>
#include <iostream>

using namespace cv;
using namespace std;


class Target : public QObject
{
    Q_OBJECT
public:
    explicit Target(int tem, int pos, QObject *parent = nullptr);
    ~Target();

    void savePicture(String path, Mat picture);

    Mat dealBack(Mat img);
    void dealBackground(Mat picture);
    void drawTrack(vector<vector<Point>> cnts, Mat picture);
    void drawCircle(Rect ret, Mat picture);
    void track(Mat deal, Mat picture);
    Rect work(Mat picture);

    void changeTT(int y);
    void changeTO(int y);

    int count;
    int temperature_threshold;
    int position_threshold;
    Mat save_picture;
    Rect location;

signals:
    void changeCount();


private:
    Arrs arrs;
    Size gs;

    Mat m_es;
    Mat background;
    Mat deal;
    Mat es;

    bool is_added;
};

#endif // TARGET_H
