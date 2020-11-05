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

void ManualSteeringWindow::on_pushButtonFwd_clicked()
{
    RequestedRobotState state;
    state.state = MANUAL_FWD;
    emit updateRequestedRobotState(state);
}

void ManualSteeringWindow::on_pushButtonStop_clicked()
{
    RequestedRobotState state;
    state.state = MANUAL_STOP;
    emit updateRequestedRobotState(state);
}

void ManualSteeringWindow::on_pushButtonLeft_clicked()
{
    RequestedRobotState state;
    state.state = MANUAL_LEFT;
    emit updateRequestedRobotState(state);
}

void ManualSteeringWindow::on_pushButtonRight_clicked()
{
    RequestedRobotState state;
    state.state = MANUAL_RIGHT;
    emit updateRequestedRobotState(state);
}

void ManualSteeringWindow::on_pushButtonBwd_clicked()
{
    RequestedRobotState state;
    state.state = MANUAL_BWD;
    emit updateRequestedRobotState(state);
}
