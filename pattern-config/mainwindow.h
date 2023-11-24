#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMessageBox>
#include <QPainter>
#include <QDir>
#include <QDebug>

#include <QGraphicsRectItem>

#include "readconfigfile.h"
#include "imageviewer.h"
#include "colordialog.h"
#include "ui_colordialog.h"
#include "configfiledialog.h"
#include "ui_configfiledialog.h"
#include "rectitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_colorSet_triggered();

    void on_action_configFile_triggered();

    void updateFileUrl(QString);

    void updateColor(QColor);

    void on_actionRegion_Info_triggered();

    void showRegionInfo(Region);

signals:

private:
    Ui::MainWindow *ui;

    ReadConfigFile* readConfigFile;
    ImageViewer* imageviewer;
    ColorDialog* colorDialog;
    ConfigFileDialog* configFileDialog;

    QGraphicsRectItem* qGraphicsRectItem;
    RectItem* rectItem;

    QString m_fileUrl;
    QColor m_color;
    QList<RectItem*> rectItemList;

    void updatePicture();
    RectItem* createMyRectItem(Region , QColor, int x, int y, int w, int h);
};
#endif // MAINWINDOW_H
