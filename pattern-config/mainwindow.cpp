#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this,&MainWindow::sendColorFileUrl, this, &MainWindow::showColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString colorFileUrl = QFileDialog::getOpenFileName(this,"选择颜色文件","D:/QtCode/signal-emulator-suite-team/pattern-config");

    ui->lineEdit->setText(colorFileUrl);

    emit sendColorFileUrl(colorFileUrl);
}

void MainWindow::showColor(QString colorFIleUrl)
{
    QImage* img=new QImage;

    if(!(img->load(colorFIleUrl))) //加载图像
    {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete img;
        return;
    }

    QImage tmpImg = img->scaled(ui->label->width(),ui->label->height());
    QPixmap pixmap=QPixmap::fromImage(tmpImg);
    ui->label->setPixmap(pixmap);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString colorFileUrl = ui->lineEdit->text();

    QStringList list1 = colorFileUrl.split("/");

    QString fileName = list1[list1.size()-1];

    QStringList list2 = fileName.split(".");

    QString colorName = list2[0];

    QString outPath = "D:/QtCode/signal-emulator-suite-team/pattern-config/output/" + colorName;
    QString bmp1Path = outPath+"/P12L-RCL";
    QString bmp2Path = outPath+"/P12L-CHL";

    QDir dir(outPath);
    if(!dir.exists())
    {
       dir.mkdir(outPath);
    }

    dir.setPath(bmp1Path);
    if(!dir.exists())
    {
       dir.mkdir(bmp1Path);
    }

    dir.setPath(bmp2Path);
    if(!dir.exists())
    {
       dir.mkdir(bmp2Path);
    }


    QImage* lastImg = new QImage;
    QImage* fullImg = new QImage;
    QString lastImgUrl = "D:/QtCode/signal-emulator-suite-team/pattern-config/P12L-RCL.bmp";
    QString fullImgUrl = colorFileUrl;

    if(!(lastImg->load(lastImgUrl))) //加载图像
    {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete lastImg;
        return;
    }

    if(!(fullImg->load(fullImgUrl))) //加载图像
    {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete fullImg;
        return;
    }

    QImage tmpImg = fullImg->scaled(4,17);

    QPainter painter;
    painter.begin(lastImg);
    painter.drawImage(0, 0, tmpImg);

    painter.end();

    //ui->label->resize(fullImg3->width(),fullImg3->height());
    //QPixmap pixmap=QPixmap::fromImage(*lastImg);
    //ui->label->setPixmap(pixmap);

    bool suc = lastImg->save(bmp1Path+"/P12L-RCL.bmp");

    if(!suc)
    {
        QMessageBox::information(this,tr("生成失败"),tr("生成失败"));
        delete lastImg;
        return;
    }else
    {
        QMessageBox::information(this,tr("生成成功"),tr("生成成功"));
        delete lastImg;
        return;
    }
}
