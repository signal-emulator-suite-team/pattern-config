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

struct Arrow
{
    QPoint pointStart;
    QPoint pointEnd;
    QColor color;
    int penWidth;
};

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

    QString m_version = "V1.0";

    ReadConfigFile* readConfigFile;
    ImageViewer* imageviewer;
    ColorDialog colorDialog;
    ConfigFileDialog configFileDialog;

    QGraphicsRectItem* qGraphicsRectItem;
    RectItem* rectItem;

    QString m_fileUrl;
    QColor m_color = QColor(191, 191, 191, 60);
    QList<RectItem*> rectItemList;
    QList<Arrow> m_arrows;

    void updatePicture();
    RectItem* createMyRectItem(Region , QColor, int x, int y, int w, int h);
    int getColoredDotsNum(QPixmap, int x, int y, int w, int h);
    bool eventFilter(QObject *watched, QEvent *event);
    void drawArrow();
    void arrowInitial();
};
#endif // MAINWINDOW_H
