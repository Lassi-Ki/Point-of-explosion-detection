#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QObject>
#include <QSlider>
#include <QMouseEvent>

class MySlider : public QSlider
{
    Q_OBJECT
public:
    explicit MySlider(QWidget *parent = nullptr);

//    void mousePressEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);

signals:

};

#endif // MYSLIDER_H
