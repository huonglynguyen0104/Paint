#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(const QPoint &topLeft, const QPoint &bottomRight)
                    :topLeft(topLeft), bottomRight(bottomRight)
{}

void Rectangle::draw(QPainter *painter){
        painter->drawRect(QRect(topLeft, bottomRight));
}

void Rectangle::update(const QPoint &point){
    bottomRight = point;
}

double Rectangle::getSize() const{

    double breite = std::abs(bottomRight.x() - topLeft.x());
    double hoehe = std::abs(bottomRight.y() - topLeft.y());

    return std::min(breite,hoehe);
}

bool Rectangle::inside(QPoint &point){
    float xmin = std::min((float)topLeft.x(),(float)bottomRight.x());
    float xmax = std::max((float)topLeft.x(),(float)bottomRight.x());
    float ymin = std::min((float)topLeft.y(),(float)bottomRight.y());
    float ymax = std::max((float)topLeft.y(),(float)bottomRight.y());

    return xmin <= (float)point.x() && ymin <= (float)point.y()
        && (float)point.x() <= xmax && (float)point.y() <= ymax;
}

void Rectangle::move(const QPoint &point){
    topLeft = topLeft + point;
    bottomRight = bottomRight + point;
}

GraphObj* Rectangle::clone() const{
    return new Rectangle(*this);
}
