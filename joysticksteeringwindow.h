#ifndef JOYSTICKSTEERINGWINDOW_H
#define JOYSTICKSTEERINGWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_pushButtonReturn_clicked();

private:
    Ui::JoystickSteeringWindow *ui;
};

#endif // JOYSTICKSTEERINGWINDOW_H
