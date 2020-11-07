#include "joysticksteeringwindow.h"
#include "ui_joysticksteeringwindow.h"
#include <QKeyEvent>
#include <QDebug>

JoystickSteeringWindow::JoystickSteeringWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JoystickSteeringWindow)
{
    //this->joypad = new JoyPad(this);
    ui->setupUi(this);
    connect(ui->joypad, SIGNAL(anyChanged(float, float)), this, SLOT(onJoystickChanged(float, float)));
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

void JoystickSteeringWindow::onJoystickChanged(float x, float y)
{
    RequestedRobotState state;
    state.state = JOYSTICK_SPEED;
    state.joystick_driving_speed = y;
    state.joystick_turning_speed = x;
    emit updateRequestedRobotState(state);
}
