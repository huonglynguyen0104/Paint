#include "graphobj.h"

GraphObj::GraphObj(){}

GraphObj::~GraphObj(){}

void GraphObj::setColor(QColor color){
    this->color = color;
}

void GraphObj::setFillMode(bool fillMode){
    this->fillMode = fillMode;
}

QColor GraphObj::getColor() const {
    return color;
}

bool GraphObj::getFillMode() const{
    return fillMode;
}

