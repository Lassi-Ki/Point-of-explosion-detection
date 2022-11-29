#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPixmap>
#include <QPalette>
#include <QBrush>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();

    ui2 = new OpenCVUi;
    ui2->hide();

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::Init()
{
    // 设置主界面背景
    QPixmap pixmap(":/pictures/0.jpg");
    // 创建一个调色板对象
    QPalette palette;
    // 用调色板的画笔把映射到pixmap上的图片画到背景上
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    // 设置窗口调色板为palette，窗口和画笔相关联
    setPalette(palette);
    // 设置窗体自动填充背景
    setAutoFillBackground(true);

    this->setWindowTitle("视频窗口");
    this->setWindowIcon(QIcon(":/pictures/0.jpg"));


    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------


    // 创建mediaPlayer
    mediaPlayer = new QMediaPlayer(this);
    // 设置mediaPlayer的QVideoWidget播放窗口，设置视频输出到widget
    mediaPlayer->setVideoOutput(ui->widget);


    // 设置播放属性
    // 1.监听信号变化函数
    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(mediaStateChanged(QMediaPlayer::State state)));
    // 2.播放进度信号变化函数
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    // 3.播放长度信号变化
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    // 4.设置播放错误关联
    connect(mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError()));


    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------


    // 设置播放按钮
    ui->startBtn->setToolTip("运行");
    ui->pathBtn->setToolTip("打开文件");
}


// ********************************************************************************************************************************
// ********************************************************************************************************************************


void MainWindow::play()
{
    switch (mediaPlayer->state()){
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}


void MainWindow::mediaStateChanged(QMediaPlayer::State state)
{
    // mediaPlayer播放过程中动态调整播放进度
    switch (state){
    case QMediaPlayer::PlayingState:
        ui->startBtn->setToolTip("暂停");
        break;
    default:
        ui->startBtn->setToolTip("开始");
        break;
    }
}


void MainWindow::positionChanged(qint64 position)
{
    // 改变播放位置
    ui->horizontalSlider->setValue(position);
}


void MainWindow::setPosition(int position)
{
    // 获取mediaPlayer进度条调整位置
    mediaPlayer->setPosition(position);
}


void MainWindow::durationChanged(qint64 duration)
{
    // 获取进度条的范围
    ui->horizontalSlider->setRange(0, duration);
}


void MainWindow::handleError()
{
    ui->startBtn->setEnabled(false);
}


// ********************************************************************************************************************************
// ********************************************************************************************************************************


void MainWindow::on_startBtn_clicked()
{
    play();
}


void MainWindow::on_pathBtn_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "选择视频文件", "C:\\Users\\Lassi\\Desktop", "(*.avi *.mp4)");
    qDebug() << file_name;
    // 设置播放内容，加载视频文件
    mediaPlayer->setMedia(QUrl::fromLocalFile(file_name));
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    setPosition(position);
}

void MainWindow::on_opencvBtn_clicked()
{

    ui2->show();

}
