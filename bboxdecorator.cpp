#include "bboxdecorator.h"

BBoxDecorator::BBoxDecorator(GraphObj* obj) : object(obj){}

void BBoxDecorator::draw(QPainter *painter) {
    object->draw(painter);

    if (object->getShowBBox()) {       
        QPoint min, max;
        calcBBox(min, max);
        painter->setPen(QPen(Qt::red, 2, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRect(min, max));
    }
}

void BBoxDecorator::update(const QPoint &point) {
    object->update(point);
}

void BBoxDecorator::move(const QPoint &point) {
    object->move(point);
}

GraphObj* BBoxDecorator::clone() const {
    return new BBoxDecorator(object->clone());
}

double BBoxDecorator::getSize () const {
    return object->getSize();
}

bool BBoxDecorator::inside(QPoint &point) {
    return object->inside(point);
}

void BBoxDecorator::calcBBox(QPoint &min, QPoint &max) const {
    object->calcBBox(min,max);
}
