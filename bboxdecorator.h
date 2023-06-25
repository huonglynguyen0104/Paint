#ifndef BBOXDECORATOR_H
#define BBOXDECORATOR_H
#include "graphobj.h"


class BBoxDecorator : public GraphObj
{
public:
    BBoxDecorator(GraphObj* obj);

    void draw(QPainter *painter) override;
    //void drawBBox(QPainter *painter);
    void update(const QPoint &point) override;
    void move(const QPoint &point) override;

    GraphObj* clone() const override;

    double getSize () const override;
    bool inside(QPoint &point) override;

    void calcBBox(QPoint &min, QPoint &max) const override;

private:
    GraphObj *object;
};

#endif // BBOXDECORATOR_H
