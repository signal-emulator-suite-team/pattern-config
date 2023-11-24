#ifndef RECTSCENE_H
#define RECTSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>

class RectScene : public QGraphicsScene
{
public:
    RectScene();
    ~RectScene();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // RECTSCENE_H
