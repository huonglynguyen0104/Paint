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

void GraphObj::setLineWidth(int mode){
    if (mode == 0) lineWidth = 1;
    if (mode == 1) lineWidth = 2;
    if (mode == 2) lineWidth = 3;
    if (mode == 3) lineWidth = 4;
}

void GraphObj::setLineShape(int mode){
    if (mode == 0) lineShape = Qt::SolidLine;
    if (mode == 1) lineShape = Qt::DashLine;
    if (mode == 2) lineShape = Qt::DotLine;
}

QColor GraphObj::getColor() const {
    return color;
}

bool GraphObj::getFillMode() const{
    return fillMode;
}

int GraphObj::getLineWidth() const{
    return lineWidth;
}
Qt::PenStyle GraphObj::getLineShape() const{
    return lineShape;
}



