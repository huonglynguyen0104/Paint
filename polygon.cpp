#include "polygon.h"

Polygon::Polygon(){}

void Polygon::draw(QPainter *painter){
    if (points.size() >= 2)
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            painter->drawLine(points[i], points[i + 1]);
        }

        if (points.size() > 2)
            painter->drawLine(points.first(), points.last());
    }
}

void Polygon::update(const QPoint &point) {
    points.append(point);
}

void Polygon::move(const QPoint &point){
    for (int i = 0; i < points.size(); i++)
    {
        points[i] = points[i] + point;
    }
}

GraphObj* Polygon::clone() const{
    return new Polygon(*this);
}

double Polygon::getSize() const{}
bool Polygon::inside(QPoint &point) {}
