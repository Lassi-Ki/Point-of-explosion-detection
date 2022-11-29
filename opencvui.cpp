#include "opencvui.h"
#include "ui_opencvui.h"

#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QLCDNumber>
#include <QComboBox>
#include <QString>
#include <QTextBrowser>
#include <QTextEdit>
#include <QDir>
#include <QFileInfo>
#include <QDesktopServices>

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

OpenCVUi::OpenCVUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCVUi)
{
    ui->setupUi(this);

    QString dir = QDir::currentPath();

    ui->textBrowser->setOpenLinks(false);
    ui->textBrowser->setOpenExternalLinks(false);

    ui->comboBox->setCurrentIndex(2);
    ui->comboBox_2->setCurrentIndex(1);

    cap = new VideoCapture;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));

    //namedWindow("opencv", WINDOW_NORMAL);

    worker = new Target(ui->comboBox->currentText().toInt(), ui->comboBox_2->currentText().toInt());

    ui->lcdNumber->display(worker->count);
    ui->lcdNumber->setDecMode();


    void(QComboBox::*fp)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBox, fp, [=](){
        worker->changeTT(ui->comboBox->currentText().toInt());
    });

    void(QComboBox::*fp1)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBox_2, fp1, [=](){
        worker->changeTO(ui->comboBox_2->currentText().toInt());
    });

    // 显示   (每次count+1时更新显示信息）
    connect(worker, &Target::changeCount, [=](){
        ui->lcdNumber->display(worker->count);
        if (worker->location.x != 0 && worker->location.y != 0)
        {
            ui->pos_x->display(worker->location.x);
            ui->pos_x->setDecMode();
            ui->pos_y->display(worker->location.y);
            ui->pos_y->setDecMode();

            QString show_txt = QString("第%1次爆炸位置: X: %2    Y: %3  <a href=\"file:///C:/Users/Lassi/Desktop/QtProject/saves/count%4.png\">查看</a> \n").arg(worker->count).arg(worker->location.x).arg(worker->location.y).arg(worker->count);
            ui->textBrowser->append(show_txt);

            // 分别保存在不同文件夹中
//            QString dir = QDir::currentPath();
            QDir dir_head(dir);
            if (dir_head.cdUp())
            {
                QString path = dir_head.path() + QString("/saves/count%1.png").arg(worker->count);
                String save_path = path.toStdString();
                worker->savePicture(save_path, worker->save_picture);
            }
        }
    });

    connect(ui->textBrowser, &QTextBrowser::anchorClicked, [=](const QUrl &link){
       auto path = link.path();
       path.remove(0, 1);
       QFileInfo info(path);
       qDebug() << path;
       if (info.isDir())
       {
           QDesktopServices::openUrl(link);
       }
       else if (info.isFile())
       {
           QDesktopServices::openUrl(QUrl::fromLocalFile(path));
       }
    });
}

OpenCVUi::~OpenCVUi()
{
    delete ui;
//    delete cap;
//    delete work;
}


void OpenCVUi::readFrame()
{
    if (cap->isOpened())
    {
        cap->read(img);
        if (!img.empty())
        {
            //cvtColor(img, result_img, COLOR_BGR2RGB);

            // 计数算法
            draw_rect = worker->work(img);

            //cout << draw_rect <<endl;

            QImage image((const uchar*)img.data, img.cols, img.rows, QImage::Format_RGB888);
            image = image.scaled(ui->showWin->width(), ui->showWin->height());
            ui->showWin->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void OpenCVUi::on_startBtn_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "选择视频文件", "C:\\Users\\Lassi\\Desktop\\QtProject\\BurstPointDetection", "(*.avi *.mp4)");
    String fileName = file_name.toStdString();

    cap->open(fileName);

    // 开始计时，每隔100毫秒更新一次，超时则发出timeout()信号
    timer->start(100);

}

void OpenCVUi::on_stopBtn_clicked()
{
    timer->stop();
    cap->release();
    img.release();
}
