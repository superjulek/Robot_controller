#ifndef MANUALSTEERINGWINDOW_H
#define MANUALSTEERINGWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include "bluetoothcommunicator.h"

namespace Ui {
class ManualSteeringWindow;
}

class ManualSteeringWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManualSteeringWindow(QWidget *parent = nullptr);
    ~ManualSteeringWindow();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void parsedTelemetry(Telemetry new_telemetry);

signals:
    void updateRequestedRobotState(RequestedRobotState state);

private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonFwd_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonLeft_clicked();

    void on_pushButtonRight_clicked();

    void on_pushButtonBwd_clicked();

private:
    Ui::ManualSteeringWindow *ui;
    QElapsedTimer *timer;
    QVector<double> time, angle, target_angle, speed, target_speed;
};

#endif // MANUALSTEERINGWINDOW_H
