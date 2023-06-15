#ifndef LINE_H
#define LINE_H
#include "qpoint.h"
#include "graphobj.h"


class Line : public GraphObj
{
public:
    Line(QPoint &startPoint, QPoint &endPoint);
    ~Line(){};

    void draw(QPainter *painter) override;
    void update(const QPoint &point) override;
    void move(const QPoint &point) override;

    GraphObj* clone() const override;

    double getSize () const override;
    bool inside(QPoint &point) override;

private:
    QPoint startPoint;
    QPoint endPoint;
};

#endif // LINE_H
