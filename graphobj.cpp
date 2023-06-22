#include "graphobj.h"

GraphObj::GraphObj(){}

GraphObj:: GraphObj(const GraphObj& object){
    color = object.color;
    fillMode = object.fillMode;
}

GraphObj& GraphObj::operator=(const GraphObj& object){
    if (this != &object) {
            color = object.color;
            fillMode = object.fillMode;
        }
    return *this;
}

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

