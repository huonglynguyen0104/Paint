#ifndef CIRCLE_H
#define CIRCLE_H
#include "qpainter.h"
#include "qpoint.h"
#include "graphobj.h"


class Circle : public GraphObj
{
public:
    Circle(const QPoint &center, int radius);
    ~Circle(){};

    void draw(QPainter *painter) override;
    void update(const QPoint &point) override;
    void move(const QPoint &point) override;

    GraphObj* clone() const override;

    double getSize () const override;
    bool inside(QPoint &point) override;

    void calcBBox(QPoint &min, QPoint &max) const override;

private:
    QPoint center;
    int radius;
};

#endif // CIRCLE_H
