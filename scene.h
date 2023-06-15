#ifndef SCENE_H
#define SCENE_H
#include "graphobj.h"


class Scene
{
public:
    Scene();
    Scene(const Scene& other);  // Copy Constructor
    Scene& operator=(const Scene& other);  // Copy Assignment Operator
    ~Scene();

    void addObj(GraphObj* obj);
    void clearCanvas();
    GraphObj* getLastObj() const;
    void draw(QPainter* painter);
    void removeLastObj();
    GraphObj* findSelectedObj(QPoint point);
    void changeObjectColor(GraphObj* selectedObj,QColor color);
    void deleteObject(GraphObj* selectedObj);
    void transformObject(GraphObj* selectedObj, QPoint point);

private:
    QVector<GraphObj*> objects;

};

#endif // SCENE_H
