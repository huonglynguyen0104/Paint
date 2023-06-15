#include "circle.h"

Circle::Circle(const QPoint &center, int radius)
              :center(center), radius(radius)
{}

void Circle::draw(QPainter *painter){
        painter->drawEllipse(center, radius, radius);
}

void Circle::update(const QPoint &point){
    int dx = point.x() - center.x();
    int dy = point.y() - center.y();
    radius = qSqrt(dx * dx + dy * dy);
}

double Circle::getSize() const{
    return 2 * radius;
}

bool Circle::inside(QPoint &point){
    float dx = (float)point.x() - (float)center.x();
    float dy = (float)point.y() - (float)center.y();
    float distance = qSqrt(dx * dx + dy * dy);
    if (distance <= radius){
        return true;
    }
    return false;
}

void Circle::move(const QPoint &point){
    center = center + point;
}

GraphObj* Circle::clone() const{
    return new Circle(*this);
}
