#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QImage>
#include <QWheelEvent>
#include <QScrollBar>

#include "rectitem.h"
#include "rectscene.h"

class ImageViewer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit  ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

    void setQImage(QImage);
    void setPixmap(QPixmap);
    void setItems(QList<RectItem*>);
    QImage getQImage();
    QPixmap getPixmap();
    void initShow();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap m_image;
    RectScene *scene;
    QList<RectItem*> m_items;

    QPointF centerAnchor;
    QPoint posAnchor;
    bool isMousePressed;
    double m_ratio = 1;
};

#endif // IMAGEVIEWER_H
