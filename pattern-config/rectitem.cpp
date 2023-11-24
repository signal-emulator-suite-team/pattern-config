#include "rectitem.h"

RectItem::RectItem()
{

}

RectItem::~RectItem()
{

}

void RectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    event->accept();

    emit sendRegionInfo(m_region);
}

void RectItem::setRegion(Region region)
{
    m_region = region;
}
