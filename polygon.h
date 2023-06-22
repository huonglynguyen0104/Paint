#ifndef POLYGON_H
#define POLYGON_H

#include <QVector>
#include "graphobj.h"

class Polygon : public GraphObj
{
public:
    Polygon();

    void draw(QPainter *painter) override;
    void update(const QPoint &point) override;
    void move(const QPoint &point) override;

    GraphObj* clone() const override;

    double getSize() const override;
    bool inside(QPoint &point) override;

private:
    QVector<QPoint> points;
};

#endif // POLYGON_H
