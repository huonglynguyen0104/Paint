#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "graphobj.h"


class Rectangle : public GraphObj
{
public:
    Rectangle(const QPoint &topLeft, const QPoint &bottomRight);
    ~Rectangle(){};

    void draw(QPainter *painter) override;
    void update(const QPoint &point) override;
    void move(const QPoint &point) override;

    GraphObj* clone() const override;

    double getSize () const override;
    bool inside(QPoint &point) override;

private:
    QPoint topLeft;
    QPoint bottomRight;
};

#endif // RECTANGLE_H
