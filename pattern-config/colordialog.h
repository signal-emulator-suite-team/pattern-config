#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QDebug>
#include <QPalette>
#include <QString>

namespace Ui {
class ColorDialog;
}

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent = nullptr);
    Ui::ColorDialog *ui;
    ~ColorDialog();

private slots:
    void on_pushButton_chooseColor_clicked();
    void updateAlpha(int value);
    void updateColor();

    void on_pushButton_defaultColor_clicked();

    void on_pushButton_colorNo_clicked();

    void on_pushButto_colorYes_clicked();

private:
    QColor m_color;

signals:
    void sendColor(QColor color);
};

#endif // COLORDIALOG_H
