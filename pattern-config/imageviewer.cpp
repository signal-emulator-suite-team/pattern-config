#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent)
    : QGraphicsView{parent},
        scene(nullptr)
{
     scene = new RectScene();
     this->setScene(scene);

     setDragMode(QGraphicsView::DragMode::NoDrag);
}

ImageViewer::~ImageViewer()
{

}

void ImageViewer::setQImage(QImage image)
{
    if(image.isNull())
        return;
    m_image = QPixmap::fromImage(image);
}

void ImageViewer::setPixmap(QPixmap pixmap)
{
    m_image = pixmap.copy();
}

void ImageViewer::setItems(QList<RectItem*> list)
{
    m_items = list;
}

QImage  ImageViewer::getQImage()
{
    return m_image.toImage();
}

QPixmap ImageViewer::getPixmap()
{
    return m_image;
}

void ImageViewer::initShow()
{
    scene->clear();
    scene->addPixmap(m_image);

    for (int i=0; i<m_items.size(); i++)
    {
        scene->addItem(m_items.at(i));
    }

    scene->update();
    this->resetTransform();
    this->setSceneRect(m_image.rect());

    scale(ratio, ratio);
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    // 记录鼠标按下时的中心点坐标
    centerAnchor = mapToScene(event->pos()) - event->pos() + QPointF(width() / 2, height() / 2);
    // 记录当前鼠标在view中的位置，用来在mouseMove事件中计算偏移
    // 此处不将view坐标转换成scene坐标的原因是优化性能，在move的过程中会产生抖动
    posAnchor = event->pos();
    isMousePressed = true;
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    QPointF offsetPos = event->pos() - posAnchor;
    if(isMousePressed){
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        centerOn(centerAnchor - offsetPos);
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    isMousePressed = false;
}

void ImageViewer::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_O) {
        this->resetTransform();
        this->setSceneRect(m_image.rect());
        this->fitInView(QRect(0, 0, m_image.width(), m_image.height()), Qt::KeepAspectRatio);
    }
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    int wheelValue = event->angleDelta().y();
    ratio = (double)wheelValue / (double)1200 + 1;
    scale(ratio, ratio);
}
