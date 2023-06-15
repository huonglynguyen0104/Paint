#include "freehandline.h"


FreeHandLine::FreeHandLine()
{}
void FreeHandLine::draw(QPainter *painter){
    painter->drawPolyline(points.data(), points.size());
}

void FreeHandLine::update(const QPoint &point){
    points.append(point);
}

double FreeHandLine::getSize() const {
    double gesamtLaenge = 0.0;

    for (int i = 1; i < points.size(); i++) {
            gesamtLaenge += std::sqrt(std::pow(points[i].x() - points[i - 1].x(), 2) + std::pow(points[i].y() - points[i - 1].y(), 2));
    }
    return gesamtLaenge;
}

bool FreeHandLine::inside(QPoint& point)
{
    for (const QPoint& p : points)
    {
        float distance = std::sqrt(std::pow(p.x() - point.x(), 2) + std::pow(p.y() - point.y(), 2));

        if (distance <= 10)
            return true;
    }
    return false;
}

void FreeHandLine::move(const QPoint &point){
    for (int i = 0; i < points.size(); i++)
    {
        points[i] = points[i] + point;
    }
}

GraphObj* FreeHandLine::clone() const{
    return new FreeHandLine(*this);
}
