#include "myslider.h"

#include <QDebug>


MySlider::MySlider(QWidget *parent) : QSlider(parent)
{

}


//void MySlider::mousePressEvent(QMouseEvent *ev)
//{
//    int currentX = ev->pos().x();
//    double per = currentX * 1.0 / this->width();
//    int value = per * (this->maximum() - this->minimum()) + this->minimum();

//    qDebug() << value;
//    this->setValue(value);

//    QSlider::mousePressEvent(ev);
//}

//void MySlider::mouseReleaseEvent(QMouseEvent *ev)
//{
//    int currentX = ev->pos().x();
//    double per = currentX * 1.0 / this->width();
//    int value = per * (this->maximum() - this->minimum()) + this->minimum();

//    qDebug() << value;
//    this->setValue(value);

//    QSlider::mousePressEvent(ev);
//}
