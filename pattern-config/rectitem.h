#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QPen>

#include "readconfigfile.h"

class RectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    RectItem();
    ~RectItem();

    void setRegion(Region);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    Region m_region;

signals:
    void sendRegionInfo(Region);
};

#endif // RECTITEM_H
