#include "manualsteeringwindow.h"
#include "ui_manualsteeringwindow.h"

#include <QKeyEvent>

ManualSteeringWindow::ManualSteeringWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManualSteeringWindow)
{
    ui->setupUi(this);
    /// Things for plotting
    this->timer = new QElapsedTimer();
    this->time = QVector<double>(100, 0.0f);
    this->angle = QVector<double>(100, 0.0f);
    this->target_angle = QVector<double>(100, 0.0f);
    this->speed = QVector<double>(100, 0.0f);
    this->target_speed = QVector<double>(100, 0.0f);
    timer->start();

    ui->plotAngle->legend->setVisible(true);
    ui->plotAngle->legend->setFont(QFont("Helvetica",9));
    ui->plotAngle->addGraph();
    ui->plotAngle->graph(0)->setPen(QPen(Qt::blue));
    ui->plotAngle->graph(0)->setName("angle");
    ui->plotAngle->addGraph();
    ui->plotAngle->graph(1)->setPen(QPen(Qt::red));
    ui->plotAngle->graph(1)->setName("target angle");
    ui->plotAngle->xAxis->setLabel("TIME [ms]");
    ui->plotAngle->yAxis->setLabel("ANGLE [°]");
    ui->plotAngle->xAxis->setRange(-5000, 0);
    ui->plotAngle->yAxis->setRange(-4.2, 4.2);
    ui->plotAngle->replot();

    ui->plotSpeed->legend->setVisible(true);
    ui->plotSpeed->legend->setFont(QFont("Helvetica",9));
    ui->plotSpeed->addGraph();
    ui->plotSpeed->graph(0)->setPen(QPen(Qt::blue));
    ui->plotSpeed->graph(0)->setName("speed");
    ui->plotSpeed->addGraph();
    ui->plotSpeed->graph(1)->setPen(QPen(Qt::red));
    ui->plotSpeed->graph(1)->setName("target speed");
    ui->plotSpeed->xAxis->setLabel("TIME [ms]");
    ui->plotSpeed->yAxis->setLabel("SPEED [rpm]");
    ui->plotSpeed->xAxis->setRange(-5000, 0);
    ui->plotSpeed->yAxis->setRange(-600, 600);
    ui->plotSpeed->replot();
    ///
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

void ManualSteeringWindow::parsedTelemetry(Telemetry new_telemetry)
{
    this->angle.removeFirst();
    this->angle.append(new_telemetry.Angle);

    this->target_angle.removeFirst();
    this->target_angle.append(new_telemetry.TargetAngle);

    this->speed.removeFirst();
    this->speed.append(new_telemetry.Speed / 1000.);

    this->target_speed.removeFirst();
    this->target_speed.append(new_telemetry.TargetSpeed / 1000.);

    this->time.removeFirst();
    double current_time = (double) this->timer->elapsed();
    this->time.append(current_time);

    QVector<double> elapsed_time = QVector<double>(this->time.size(),0.0f);
    for (int i = 0; i < this->time.size(); ++i)
    {
        elapsed_time[i] = this->time[i] - current_time;
    }

    this->ui->plotAngle->graph(0)->setData(elapsed_time, this->angle);
    this->ui->plotAngle->graph(1)->setData(elapsed_time, this->target_angle);
    this->ui->plotAngle->replot();

    this->ui->plotSpeed->graph(0)->setData(elapsed_time, this->speed);
    this->ui->plotSpeed->graph(1)->setData(elapsed_time, this->target_speed);
    this->ui->plotSpeed->replot();


}
