#include "line.h"

Line::Line(QPoint &startPoint, QPoint &endPoint)
            : startPoint(startPoint), endPoint(endPoint)
{}

void Line::draw(QPainter *painter){
    painter->drawLine(startPoint, endPoint);
}

void Line::update(const QPoint &point){
    endPoint = point;
}

double Line::getSize() const {
    return std::sqrt(std::pow(endPoint.x() - startPoint.x(), 2)+std::pow(endPoint.y() - startPoint.y(), 2));
}

bool Line::inside(QPoint& point){
    //L(t) = P1 + t (P2 - P1) = P1 + tv
    float v_x = endPoint.x() - startPoint.x();
    float v_y = endPoint.y() - startPoint.y();
    float vLengthSquare = v_x * v_x + v_y * v_y;

    //Skalarprodukts: (R - L(t0)).v = 0 => t0 = (R - P).v / |v|²
    float RP_x = point.x() - startPoint.x();
    float RP_y = point.y() - startPoint.y();
    float t0 = (RP_x * v_x + RP_y * v_y)/ vLengthSquare;

    if (t0 <= 1 && t0 >= 0){
        float t0_x = startPoint.x() + t0 * v_x;
        float t0_y = startPoint.y() + t0 * v_y;
        float distance = std::sqrt(std::pow(point.x() - t0_x, 2)+std::pow(point.y() - t0_y, 2));
        if(distance <= 10)
            return true;
    }
    return false;
}

void Line::move(const QPoint &point){
    startPoint = startPoint + point;
    endPoint = endPoint + point;
}

GraphObj* Line::clone() const{
    return new Line(*this);
}

void Line::calcBBox(QPoint &min, QPoint &max) const {
    min.setX(std::min(startPoint.x(), endPoint.x()));
    min.setY(std::min(startPoint.y(), endPoint.y()));
    max.setX(std::max(startPoint.x(), endPoint.x()));
    max.setY(std::max(startPoint.y(), endPoint.y()));
}
