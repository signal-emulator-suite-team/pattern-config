#include "colordialog.h"
#include "ui_colordialog.h"

ColorDialog::ColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);

    m_color = QColor(191, 191, 191, 60);

    QPalette pal = ui->graphicsView_rect->palette();

    pal.setColor(QPalette::Base, m_color);

    ui->graphicsView_rect->setPalette(pal);

    ui->horizontalSlider->setRange(0,255);

    ui->horizontalSlider->setValue(m_color.alpha());

    ui->lineEdit_alpha->setText(QString::number(m_color.alpha()));

    //接收slider的值，实时修改透明度的值以及颜色
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(updateAlpha(int)));
}

ColorDialog::~ColorDialog()
{
    delete ui;
}

void ColorDialog::updateAlpha(int value)
{
    QString text = QString::number(value);

    ui->lineEdit_alpha->setText(text);

    m_color.setAlpha(value);

    updateColor();
}

void ColorDialog::on_pushButton_chooseColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red,this,tr("颜色对话框"));

    m_color.setRed(color.red());
    m_color.setGreen(color.green());
    m_color.setBlue(color.blue());

    updateColor();
}

void ColorDialog::updateColor()
{
    QPalette pal = ui->graphicsView_rect->palette();

    pal.setColor(QPalette::Base, m_color);

    ui->graphicsView_rect->setPalette(pal);
}

void ColorDialog::on_pushButton_defaultColor_clicked()
{
    m_color = QColor(191, 191, 191, 60);

    ui->horizontalSlider->setValue(m_color.alpha());

    ui->lineEdit_alpha->setText(QString::number(m_color.alpha()));

    updateColor();
}

void ColorDialog::on_pushButton_colorNo_clicked()
{
    this->close();
}

void ColorDialog::on_pushButto_colorYes_clicked()
{
    emit sendColor(m_color);

    this->close();
}
