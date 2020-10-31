#include "configurationwindow.h"
#include "ui_configurationwindow.h"
#include <QKeyEvent>
#include <QtDebug>

ConfigurationWindow::ConfigurationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigurationWindow)
{
    ui->setupUi(this);
}

ConfigurationWindow::~ConfigurationWindow()
{
    delete ui;
}

void ConfigurationWindow::on_pushButtonReturn_clicked()
{
    this->hide();
}

void ConfigurationWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Back:
        this->hide();
    }
}

void ConfigurationWindow::on_pushButtonAngleRefresh_clicked()
{
    emit requestAnglePID();
}


void ConfigurationWindow::parsedAnglePID(PID_Coefs coefs)
{
    this->ui->doubleSpinBoxAngleKp->setValue(coefs.Kp);
    this->ui->doubleSpinBoxAngleKi->setValue(coefs.Ki);
    this->ui->doubleSpinBoxAngleKd->setValue(coefs.Kd);
}

void ConfigurationWindow::parsedSpeedPID(PID_Coefs coefs)
{
    this->ui->doubleSpinBoxSpeedKp->setValue(coefs.Kp);
    this->ui->doubleSpinBoxSpeedKi->setValue(coefs.Ki);
    this->ui->doubleSpinBoxSpeedKd->setValue(coefs.Kd);
}

void ConfigurationWindow::on_pushButtonSpeedRefresh_clicked()
{
    emit requestSpeedPID();
}

void ConfigurationWindow::on_pushButtonAngleSend_clicked()
{
    PID_Coefs coefs;
    coefs.Kp = this->ui->doubleSpinBoxAngleKp->value();
    coefs.Ki = this->ui->doubleSpinBoxAngleKi->value();
    coefs.Kd = this->ui->doubleSpinBoxAngleKd->value();
    qDebug() << coefs.Kp;
    emit updateAnglePID(coefs);
}

void ConfigurationWindow::on_pushButtonSpeedSend_clicked()
{
    PID_Coefs coefs;
    coefs.Kp = this->ui->doubleSpinBoxSpeedKp->value();
    coefs.Ki = this->ui->doubleSpinBoxSpeedKi->value();
    coefs.Kd = this->ui->doubleSpinBoxSpeedKd->value();
    emit updateSpeedPID(coefs);
}
