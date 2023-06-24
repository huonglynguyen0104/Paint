#ifndef CANVAS_H
#define CANVAS_H

#include "scene.h"
#include <QFrame>

class Canvas : public QFrame
{
	Q_OBJECT

public:
	enum PrimitiveMode {
        NONE, FREE_HAND, CIRCLE, LINE, TRIANGLE, RECTANGLE, POLYGON
	};

    enum InteractionMode { CREAT, DEL, COL, TRAFO };

    enum LineWidth { WIDTH1, WIDTH2, WIDTH3, WIDTH4 };

    enum LineShape { SOLIDLINE, DASHLINE, DOTLINE };

	Canvas(QWidget *parent = 0);
	~Canvas();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void clearCanvas(void);
	void setPrimitiveMode(int mode);
    void setInteractionMode(int mode);
    void setColor(QColor color);
    void setFillMode(bool fillMode);
    void setLineWidth(int mode);
    void setLineShape(int mode);
    void changeBGColor(QColor color);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	bool dragging;
	PrimitiveMode type;
    InteractionMode mode = CREAT;
    LineWidth lineWidth = WIDTH1;
    LineShape lineShape = SOLIDLINE;
    QColor color;
    QColor BGColor = Qt::white;
    bool fillMode = true;
    Scene scene;
    QPoint startPos;
    QPoint currentPos;
    QPoint lastPos;
    QPoint displacement;
    GraphObj* selectedObj = nullptr;
};

#endif // CANVAS_H
