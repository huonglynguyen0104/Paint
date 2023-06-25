#include "scene.h"
#include "bboxdecorator.h"

Scene::Scene(){}

Scene::~Scene()
{
    clearCanvas();
}

Scene::Scene(const Scene& other){
    for (GraphObj* obj : other.objects)
    {
        objects.append(obj->clone());
    }
}
Scene& Scene::operator=(const Scene& other){
    if (this != &other)
    {
        clearCanvas();

        for (GraphObj* obj : other.objects)
        {
            objects.append(obj->clone());
        }
    }
    return *this;
}

void Scene::addObj(GraphObj* obj)
{
    if (obj)
    {
        objects.append(obj);
    }
}

void Scene::clearCanvas()
{
    qDeleteAll(objects);
    objects.clear();
}

GraphObj* Scene::getLastObj() const
{
    if (!objects.isEmpty())
    {
        return objects.last();
    }
    return nullptr;
}

void Scene::draw(QPainter* painter)
{
    for (GraphObj* obj : objects)
    {
        if (obj)
        {
            if(obj->getFillMode()){
                painter->setBrush(obj->getColor());
                painter->setPen(QPen(obj->getColor(),obj->getLineWidth(),obj->getLineShape()));
                obj->draw(painter);
            }else{
                painter->setPen(QPen(obj->getColor(),obj->getLineWidth(),obj->getLineShape()));
                painter->setBrush(Qt::NoBrush);
                obj->draw(painter);
            }
            if(obj->getShowBBox()){
                BBoxDecorator *newBBoxObj = new BBoxDecorator(obj);
                newBBoxObj->draw(painter);
            }
        }
    }
}

void Scene::removeLastObj(){
    if (!objects.isEmpty())
    { 
        objects.removeLast();
    }
}

GraphObj* Scene::findSelectedObj(QPoint point){
    for (auto obj : objects){
        if(obj->inside(point)) return obj;
    }
    return nullptr;
}

void Scene::changeObjectColor(GraphObj* selectedObj, QColor color){
    for (int i = 0; i< objects.size(); i++){
        if(objects[i] == selectedObj){
            objects[i]->setColor(color);
            break;
        }
    }
}

void Scene::deleteObject(GraphObj* selectedObj){
    for (int i = 0; i< objects.size(); i++){
        if(objects[i] == selectedObj){
            objects.erase(objects.begin() + i);
            break;
        }
    }
}

void Scene::transformObject(GraphObj* selectedObj, QPoint point){
    for (int i = 0; i< objects.size(); i++){
        if(objects[i] == selectedObj){
            objects[i]->move(point);
            break;
        }
    }
}

