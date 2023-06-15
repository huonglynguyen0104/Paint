#ifndef FREEHANDLINE_H
#define FREEHANDLINE_H
#include "qpoint.h"
#include "graphobj.h"


class FreeHandLine : public GraphObj
{
public:
    FreeHandLine();
    ~FreeHandLine(){};

    void draw(QPainter *painter) override;
    void update(const QPoint &point) override;
    void move(const QPoint &point) override;

    GraphObj* clone() const override;

    double getSize () const override;
    bool inside(QPoint &point) override;

private:
    QVector<QPoint> points;
};

#endif // FREEHANDLINE_H
