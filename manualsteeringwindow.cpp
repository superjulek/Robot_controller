#include "manualsteeringwindow.h"
#include "ui_manualsteeringwindow.h"

#include <QKeyEvent>

ManualSteeringWindow::ManualSteeringWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManualSteeringWindow)
{
    ui->setupUi(this);
}

ManualSteeringWindow::~ManualSteeringWindow()
{
    delete ui;
}

void ManualSteeringWindow::on_pushButtonReturn_clicked()
{
    this->hide();
}

void ManualSteeringWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Back:
        this->hide();
    }
}
