#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("pattern-config - "+m_fileUrl+" - R:"+ QString::number(m_color.red())+",G:"+ QString::number(m_color.green())+",B:"+ QString::number(m_color.blue())+",A:"+ QString::number(m_color.alpha()));
    ui->dockWidget->setWindowTitle("Region Info");
    ui->label_category->setText("");
    ui->label_dir->setText("");
    ui->label_index->setText("");
    ui->label_color->setText("");

    m_color = QColor(191, 191, 191, 60);

    colorDialog = new ColorDialog;
    configFileDialog = new ConfigFileDialog;
    readConfigFile = new ReadConfigFile;
    imageviewer = new ImageViewer(this);

    ui->horizontalLayout->addWidget(imageviewer);
    imageviewer->hide();

    connect(colorDialog, SIGNAL(sendColor(QColor)),this, SLOT(updateColor(QColor)));
    connect(configFileDialog, SIGNAL(sendFileUrl(QString)),this, SLOT(updateFileUrl(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateColor(QColor color)
{
    m_color = color;
    this->setWindowTitle("pattern-config - "+m_fileUrl+" - R:"+ QString::number(m_color.red())+",G:"+ QString::number(m_color.green())+",B:"+ QString::number(m_color.blue())+",A:"+ QString::number(m_color.alpha()));
    updatePicture();
}

void MainWindow::updateFileUrl(QString fileUrl)
{
    m_fileUrl = fileUrl;
    this->setWindowTitle("pattern-config - "+m_fileUrl+" - R:"+ QString::number(m_color.red())+",G:"+ QString::number(m_color.green())+",B:"+ QString::number(m_color.blue())+",A:"+ QString::number(m_color.alpha()));
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
        rectItem = createMyRectItem(config.regions[i], m_color,config.regions[i].roi[0],config.regions[i].roi[1],config.regions[i].roi[2],config.regions[i].roi[3]);
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
    colorDialog -> show();
}

void MainWindow::on_action_configFile_triggered()
{
    configFileDialog -> show();
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

    return rectItem;
}

void MainWindow::showRegionInfo(Region region)
{
    ui->label_category->setText(region.category);
    ui->label_dir->setText("DirH: "+ QString::number(region.dirH)+"\nDirV: "+ QString::number(region.dirV));
    ui->label_index->setText(region.prefix+QString::number(region.indexStart)+region.suffix);
    ui->label_color->setText("Channel_R: Red\nChannel_G: Yellow\nChannel_B: White");
}
