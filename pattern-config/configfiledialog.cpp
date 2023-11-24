#include "configfiledialog.h"
#include "ui_configfiledialog.h"

ConfigFileDialog::ConfigFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigFileDialog)
{
    ui->setupUi(this);

    configIniWrite = new QSettings("PatternConfigSettings.ini", QSettings::IniFormat);
}

ConfigFileDialog::~ConfigFileDialog()
{
    delete ui;
}

void ConfigFileDialog::on_pushButton_configFile_clicked()
{
    QString lastConfigPath = configIniWrite -> value("lastConfigPath").toString();

    QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), lastConfigPath, tr("config files(*.config);;all files(*)"));

    if (filePath != "")
    {
        ui -> lineEdit_configFile -> setText(filePath);
    }

    configIniWrite -> setValue("lastSofilePath", filePath);

    m_fileUrl = filePath;
}

void ConfigFileDialog::on_pushButton_configNo_clicked()
{
    this -> close();
}

void ConfigFileDialog::on_pushButton_configYes_clicked()
{
    if (m_fileUrl == "")
    {
        QMessageBox::warning(this, "警告", "文件路径不能为空");

        return;
    }

    emit sendFileUrl(m_fileUrl);

    this -> close();
}
