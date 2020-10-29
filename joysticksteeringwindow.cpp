#include "joysticksteeringwindow.h"
#include "ui_joysticksteeringwindow.h"
#include <QKeyEvent>

JoystickSteeringWindow::JoystickSteeringWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JoystickSteeringWindow)
{
    ui->setupUi(this);
}

JoystickSteeringWindow::~JoystickSteeringWindow()
{
    delete ui;
}

void JoystickSteeringWindow::on_pushButtonReturn_clicked()
{
    this->hide();
}

void JoystickSteeringWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Back:
        this->hide();
    }
}
