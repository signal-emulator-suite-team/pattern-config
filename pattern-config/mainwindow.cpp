#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("pattern-config " + m_version + " - "+m_fileUrl+" - R:"+ QString::number(m_color.red())+",G:"+ QString::number(m_color.green())+",B:"+ QString::number(m_color.blue())+",A:"+ QString::number(m_color.alpha()));
    ui->dockWidget->setWindowTitle("Region Info");
    ui->label_category->setText("");
    ui->label_dir->setText("");
    ui->label_index->setText("");
    ui->label_color->setText("");

    m_color = QColor(191, 191, 191, 60);

    readConfigFile = new ReadConfigFile;
    imageviewer = new ImageViewer(this);

    ui->horizontalLayout->addWidget(imageviewer);
    imageviewer->hide();

    connect(&colorDialog, SIGNAL(sendColor(QColor)),this, SLOT(updateColor(QColor)));
    connect(&configFileDialog, SIGNAL(sendFileUrl(QString)),this, SLOT(updateFileUrl(QString)));
    arrowInitial();

    ui->label_dir->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateColor(QColor color)
{
    m_color = color;
    this->setWindowTitle("pattern-config " + m_version + " - "+m_fileUrl+" - R:"+ QString::number(m_color.red())+",G:"+ QString::number(m_color.green())+",B:"+ QString::number(m_color.blue())+",A:"+ QString::number(m_color.alpha()));
    updatePicture();
}

void MainWindow::updateFileUrl(QString fileUrl)
{
    m_fileUrl = fileUrl;
    this->setWindowTitle("pattern-config " + m_version + " - "+m_fileUrl+" - R:"+ QString::number(m_color.red())+",G:"+ QString::number(m_color.green())+",B:"+ QString::number(m_color.blue())+",A:"+ QString::number(m_color.alpha()));
    updatePicture();
}

void MainWindow::updatePicture()
{
    if (m_fileUrl == "")
    {
        QMessageBox::warning(this, "警告", "文件路径不能为空");

        return;
    }

    rectItemList.clear();

    Config config = readConfigFile->getConfig(m_fileUrl);

    QPixmap mapImg(config.imageFile);
    imageviewer->setPixmap(mapImg);

    for (int i=0; i<config.regions.size(); i++)
    {
        Region region = config.regions[i];

        int coloredNum = getColoredDotsNum(mapImg,region.roi[0],region.roi[1],region.roi[2],region.roi[3]);
        region.indexEnd =  region.indexStart + coloredNum - 1;
        rectItem = createMyRectItem(region, m_color,region.roi[0],region.roi[1],region.roi[2],region.roi[3]);
        rectItemList.append(rectItem);
    }

    for (int i=0; i<rectItemList.size(); i++)
    {
        connect(rectItemList[i], SIGNAL(sendRegionInfo(Region)), this, SLOT(showRegionInfo(Region)));
    }

    imageviewer->setItems(rectItemList);
    imageviewer->initShow();
    imageviewer->show();
}

void MainWindow::on_action_colorSet_triggered()
{
    colorDialog.exec();
}

void MainWindow::on_action_configFile_triggered()
{
    configFileDialog.exec();
}

void MainWindow::on_actionRegion_Info_triggered()
{
    if (ui->dockWidget->isHidden())
    {
        ui->dockWidget->show();

    }else
    {
        ui->dockWidget->hide();
    }
}

RectItem* MainWindow::createMyRectItem(Region region, QColor color, int x, int y, int w, int h)
{
    RectItem* rectItem = new RectItem();

    rectItem->setRegion(region);

    QPen pen;
    pen.setColor(color);
    pen.setWidth(0);
    rectItem->setRect(x, y, w, h);
    rectItem->setPen(pen);
    rectItem->setBrush(QBrush(QColor(color)));
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);

    rectItem->setFlag(QGraphicsItem::ItemIsMovable, false);
    rectItem->setFlag(QGraphicsItem::ItemIsSelectable,true);

    return rectItem;
}

void MainWindow::showRegionInfo(Region region)
{
    ui->label_category->setText("Category: " + region.category);

    ui->label_index->setText(region.prefix+" "+QString::number(region.indexStart)+" "+region.suffix+" ~ \n"+region.prefix+" "+QString::number(region.indexEnd)+" "+region.suffix);

    QColor color;

    if (region.channel=="R")
    {
        ui->label_color->setText("Channel_R: Red");
        color=QColor(255,0,0,150);
    }else if (region.channel=="G")
    {
        ui->label_color->setText("Channel_G: Yellow");
        color=QColor(255,255,0,150);
    }else if (region.channel=="B")
    {
        ui->label_color->setText("Channel_B: White");
        color=QColor(255,255,255,150);
    }

    //qDebug()<<("DirH: "+ QString::number(region.dirH)+"\nDirV: "+ QString::number(region.dirV));
    if (region.dirH==0)
    {
        m_arrows[2].color=color;
        m_arrows[0].color=QColor(191,191,191,150);
    }else if (region.dirH==1)
    {
        m_arrows[0].color=color;
        m_arrows[2].color=QColor(191,191,191,150);
    }

    if (region.dirV==0)
    {
        m_arrows[3].color=color;
        m_arrows[1].color=QColor(191,191,191,150);
    }else if (region.dirV==1)
    {
        m_arrows[1].color=color;
        m_arrows[3].color=QColor(191,191,191,150);
    }

    update();
}

int MainWindow::getColoredDotsNum(QPixmap pixmap, int x, int y, int w, int h)
{
    int num = 0;

    QImage image = pixmap.toImage();

    for (int i = x; i < x + w; i++)
    {
        for (int j = y; j < y + h; j++)
        {
            QRgb pixelValue = image.pixel(i, j);

            int r = qRed(pixelValue);
            int g = qGreen(pixelValue);
            int b = qBlue(pixelValue);

            if (r != 0 || g != 0 || b != 0)
            {
                num++;
            }
        }
    }

    return num;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->label_dir && event->type() == QEvent::Paint) {
        drawArrow();
    }

    return QWidget::eventFilter(watched, event);
}

void MainWindow::drawArrow()
{
    QPainter painter(ui->label_dir);

    QPen pen;

    for (int i=0;i<m_arrows.size();i++)
    {
        pen.setColor(m_arrows[i].color);
        pen.setWidth(m_arrows[i].penWidth);
        pen.setStyle(Qt::SolidLine);

        painter.setPen(pen);
        painter.setBrush(QBrush(pen.color()));

        qreal arrowSize=6;
        QLineF line(m_arrows[i].pointEnd,m_arrows[i].pointStart);

        double PI = acos(-1);

        double angle=std::atan2(-line.dy(),line.dx());
        QPointF arrowPos1=line.p1()+QPoint(sin(angle+PI/3)*arrowSize,cos(angle+PI/3)*arrowSize);
        QPointF arrowPos2=line.p1()+QPoint(sin(angle+PI-PI/3)*arrowSize,cos(angle+PI-PI/3)*arrowSize);

        QPolygonF polygon;
        polygon<<line.p1()<<arrowPos1<<arrowPos2;
        painter.drawLine(line);
        painter.drawPolygon(polygon);
    }
}

void MainWindow::arrowInitial()
{
    m_arrows.clear();

    Arrow arrow;
    arrow.pointStart=QPoint(ui->label_dir->width()/2,ui->label_dir->height()/2);
    arrow.pointEnd=QPoint(10,ui->label_dir->height()/2);
    arrow.color=QColor(191,191,191,150);
    arrow.penWidth=3;

    m_arrows.append(arrow);
    arrow.pointStart=QPoint(ui->label_dir->width()/2,ui->label_dir->height()/2);
    arrow.pointEnd=QPoint(ui->label_dir->width()/2,10);
    arrow.color=QColor(191,191,191,150);
    arrow.penWidth=3;
    m_arrows.append(arrow);

    arrow.pointStart=QPoint(ui->label_dir->width()/2,ui->label_dir->height()/2);
    arrow.pointEnd=QPoint(ui->label_dir->width()-10,ui->label_dir->height()/2);
    arrow.color=QColor(191,191,191,150);
    arrow.penWidth=3;
    m_arrows.append(arrow);

    arrow.pointStart=QPoint(ui->label_dir->width()/2,ui->label_dir->height()/2);
    arrow.pointEnd=QPoint(ui->label_dir->width()/2,ui->label_dir->height()-10);
    arrow.color=QColor(191,191,191,150);
    arrow.penWidth=3;
    m_arrows.append(arrow);
}
