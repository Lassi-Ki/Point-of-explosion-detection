#ifndef OPENCVUI_H
#define OPENCVUI_H

#include <QMainWindow>
#include <QTimer>

#include "target.h"


namespace Ui {
class OpenCVUi;
}

class OpenCVUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenCVUi(QWidget *parent = nullptr);
    ~OpenCVUi();


private slots:
    void readFrame();
    void on_startBtn_clicked();
    void on_stopBtn_clicked();

private:
    Ui::OpenCVUi *ui;

    VideoCapture *cap;
    Target *worker;
    QTimer *timer;

    bool sign;
    Mat img;
    Mat result_img;
    Rect draw_rect;
};

#endif // OPENCVUI_H
