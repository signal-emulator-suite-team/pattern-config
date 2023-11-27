#ifndef CONFIGFILEDIALOG_H
#define CONFIGFILEDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

#include "readconfigfile.h"

namespace Ui {
class ConfigFileDialog;
}

class ConfigFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigFileDialog(QWidget *parent = nullptr);
    Ui::ConfigFileDialog *ui;
    ~ConfigFileDialog();

private slots:
    void on_pushButton_configFile_clicked();

    void on_pushButton_configNo_clicked();

    void on_pushButton_configYes_clicked();

private:
    QSettings *configIniWrite;
    QString m_fileUrl;

signals:
    void sendFileUrl(QString fileUrl);
};

#endif // CONFIGFILEDIALOG_H
