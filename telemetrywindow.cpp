#include "telemetrywindow.h"
#include "ui_telemetrywindow.h"
#include <QKeyEvent>

TelemetryWindow::TelemetryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelemetryWindow)
{
    ui->setupUi(this);
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
