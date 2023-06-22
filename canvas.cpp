#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <math.h>
#include "canvas.h"
#include "freehandline.h"
#include "line.h"
#include "circle.h"
#include "polygon.h"
#include "rectangle.h"

Canvas::Canvas(QWidget *parent)
	: QFrame(parent)
{
	setFrameStyle(QFrame::Box);
	setMouseTracking(true);

    type = NONE;
	dragging = false;
}

Canvas::~Canvas(){}

QSize Canvas::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize Canvas::sizeHint() const
{
    return QSize(640, 480);
}

void Canvas::clearCanvas(void)
{
    scene.clearCanvas();

}

void Canvas::setPrimitiveMode(int mode)
{
	type = (Canvas::PrimitiveMode)mode;
}

void Canvas::setInteractionMode(int mode){
    this->mode = (Canvas::InteractionMode)mode;
}

void Canvas::setObjColor(QColor color){
    this->color = color;
}

void Canvas::setFillMode(bool fillMode){
    this->fillMode = fillMode;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);  // parent class draws border

    QPainter painter(this);

    // white background (inside parent's border)
    painter.fillRect(QRect(1, 1, width() - 2, height() - 2), Qt::white);

    scene.draw(&painter);

    // The following is just a basic example and to be removed...

//    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
//    painter.drawLine(QPoint(2, height()/2), QPoint(width()-2, height()/2));
//    painter.drawLine(QPoint(width()/2, 2), QPoint(width()/2, height()-2));
//    painter.setPen(Qt::blue);
//    painter.setBrush(Qt::darkGreen);
//    painter.drawEllipse(QPoint(width()/2, height()/2), 8, 8);

}

void Canvas::resizeEvent(QResizeEvent *event) 
{
	QFrame::resizeEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (mode == CREAT && event->button() == Qt::LeftButton) {
		dragging = true;

        startPos = event->pos();
        currentPos = startPos;

        GraphObj* newObj = nullptr;
        switch (type)
        {
            case FREE_HAND:
                newObj = new FreeHandLine();
                break;
            case CIRCLE:
                newObj = new Circle(startPos, 0);
                break;
            case LINE:
                newObj = new Line(startPos, currentPos);
                break;
            case RECTANGLE:
                newObj = new Rectangle(startPos, currentPos);
                break;
            case POLYGON:
                newObj = new Polygon();
            default:
                break;
        }
        if (newObj)
        {
            newObj->setColor(color);
            newObj->setFillMode(fillMode);
            scene.addObj(newObj);
            update();
        }
	}
    if (mode == COL){
        if (event->button() == Qt::LeftButton){
            startPos = event->pos();
            currentPos = startPos;

            selectedObj = scene.findSelectedObj(currentPos);
            qDebug() << "checkInside. "<< selectedObj;
            if (selectedObj){
                scene.changeObjectColor(selectedObj,color);
                update();
            }
        }
    }
    if (mode == DEL){
        if (event->button() == Qt::LeftButton){
            startPos = event->pos();
            currentPos = startPos;

            selectedObj = scene.findSelectedObj(currentPos);
            qDebug() << "checkInside. "<< selectedObj;
            if (selectedObj){
                scene.deleteObject(selectedObj);
                update();
            }
        }
    }
    if (mode == TRAFO){
        if (event->button() == Qt::LeftButton){
            dragging = true;

            startPos = event->pos();
            currentPos = startPos;

            selectedObj = scene.findSelectedObj(currentPos);
            qDebug() << "checkInside. "<< selectedObj;
            lastPos = currentPos;
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (mode == CREAT && (event->buttons() & Qt::LeftButton) && dragging) {
        currentPos = event->pos();

        GraphObj* lastObj = scene.getLastObj();
        if (lastObj)
        {
            lastObj->update(currentPos);
            update();
        }
    }
    if (mode == TRAFO && (event->buttons() & Qt::LeftButton) && dragging){
        if (selectedObj){
            currentPos = event->pos();
            displacement = currentPos - lastPos;
            scene.transformObject(selectedObj, displacement);
            lastPos = currentPos;
            update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (mode == CREAT && event->button() == Qt::LeftButton && dragging) {
        currentPos = event->pos();
		dragging = false;

        GraphObj* lastObj = scene.getLastObj();
        if (lastObj)
        {
            lastObj->update(currentPos);
        }

        // Check the size of the last object
        if (lastObj && lastObj->getSize() < 20){
            scene.removeLastObj();
            update();
        }
    }
    if (mode == TRAFO && event->button() == Qt::LeftButton && dragging){
        if (selectedObj){
            currentPos = event->pos();
            dragging = false;
        }
    }

}

