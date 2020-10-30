#include "telemetrywindow.h"
#include "ui_telemetrywindow.h"

#include <QKeyEvent>
#include <QDateTime>
#include <QTextStream>

#define FILE_LOCATION "/storage/emulated/0/ROBOT/"

TelemetryWindow::TelemetryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelemetryWindow)
{
    ui->setupUi(this);
    this->ui->pushButtonStopDump->setEnabled(false);
}

TelemetryWindow::~TelemetryWindow()
{
    delete ui;
}

void TelemetryWindow::on_pushButtonReturn_clicked()
{
    this->hide();
}

void TelemetryWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Back:
        this->hide();
    }
}

void TelemetryWindow::parsedTelemetry(Telemetry new_telemetry)
{
    this->ui->progressBarBattery->setValue(new_telemetry.Battery);
    this->ui->progressBarTargetAngle->setValue(new_telemetry.TargetAngle * 1000);
    this->ui->progressBarAngle->setValue(new_telemetry.Angle * 1000);
    this->ui->progressBarTargetSpeed->setValue(new_telemetry.TargetSpeed);
    this->ui->progressBarSpeed->setValue(new_telemetry.Speed);
    if (this->file_opened)
    {
        QTextStream stream(this->file);
        stream << this->timer.elapsed() << "\t" << new_telemetry.TargetAngle << "\t" << new_telemetry.Angle << \
                  "\t" << new_telemetry.TargetSpeed << "\t" << new_telemetry.Speed << Qt::endl;
    }
}

void TelemetryWindow::on_pushButtonStartDump_clicked()
{
    this->ui->pushButtonStopDump->setEnabled(true);
    this->ui->pushButtonStartDump->setEnabled(false);
    this->file_opened = true;
    this->timer.restart();
    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString(QLatin1String("yyyyMMdd-hhmm"));
    QString filepath = QString(FILE_LOCATION) + QString("ROBOTLOG") + timestamp + QString(".txt");
    this->file = new QFile(filepath);
    this->file->open(QIODevice::WriteOnly | QIODevice::Text);
}

void TelemetryWindow::on_pushButtonStopDump_clicked()
{
    this->ui->pushButtonStartDump->setEnabled(true);
    this->ui->pushButtonStopDump->setEnabled(false);
    this->file->close();
    this->file_opened = false;

}
