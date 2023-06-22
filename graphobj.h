#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H
#include "qpainter.h"
#include <cmath>

class GraphObj
{
public:
    GraphObj();
    GraphObj(const GraphObj& object);
    GraphObj& operator=(const GraphObj& object);
    ~GraphObj();

    virtual void draw(QPainter *painter) = 0;
    virtual void update(const QPoint &point) = 0;
    virtual void move(const QPoint &point) = 0;

    virtual GraphObj* clone() const = 0;

    void setColor(QColor color);
    QColor getColor() const;

    void setFillMode(bool fillMode);
    bool getFillMode() const;

    virtual double getSize () const = 0;
    virtual bool inside(QPoint &point) = 0;

protected:
    QColor color = Qt::black;
    bool fillMode = true;

};

#endif // GRAPHOBJ_H
