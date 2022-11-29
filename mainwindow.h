#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

#include "opencvui.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;
    OpenCVUi *ui2;

    void Init();

private slots:

    // 播放
    void play();
    // 播放状态
    void mediaStateChanged(QMediaPlayer::State state);
    // 改变播放位置
    void positionChanged(qint64 position);
    // 获取播放位置
    void setPosition(int position);
    // 播放长度
    void durationChanged(qint64 duration);
    // 播放异常的抛出
    void handleError();

    void on_startBtn_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_pathBtn_clicked();
    void on_opencvBtn_clicked();
};
#endif // MAINWINDOW_H
