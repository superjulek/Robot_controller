#ifndef JOYSTICKSTEERINGWINDOW_H
#define JOYSTICKSTEERINGWINDOW_H

#include <QMainWindow>
#include "bluetoothcommunicator.h"
#include "joypad.h"

namespace Ui {
class JoystickSteeringWindow;
}

class JoystickSteeringWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JoystickSteeringWindow(QWidget *parent = nullptr);
    ~JoystickSteeringWindow();
    void keyPressEvent(QKeyEvent *event);

signals:
    void updateRequestedRobotState(RequestedRobotState state);

private slots:
    void on_pushButtonReturn_clicked();
    void onJoystickChanged(float, float);

private:
    Ui::JoystickSteeringWindow *ui;
};

#endif // JOYSTICKSTEERINGWINDOW_H
