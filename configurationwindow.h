#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QMainWindow>

#include "bluetoothcommunicator.h"

namespace Ui {
class ConfigurationWindow;
}

class ConfigurationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigurationWindow(QWidget *parent = nullptr);
    ~ConfigurationWindow();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void parsedAnglePID(PID_Coefs);
    void parsedSpeedPID(PID_Coefs);
    void parsedManualSpeeds(Speeds);
    void parsedJoystickSpeeds(Speeds);
private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonAngleRefresh_clicked();

    void on_pushButtonSpeedRefresh_clicked();

    void on_pushButtonSpeedSend_clicked();

    void on_pushButtonAngleSend_clicked();

    void on_pushButtonManualSpeedsRefresh_clicked();

    void on_pushButtonJoystickSpeedsRefresh_clicked();

    void on_pushButtonManualSpeedsSend_clicked();

    void on_pushButtonJoystickSpeedsSend_clicked();

signals:
    void requestAnglePID();
    void requestSpeedPID();
    void updateAnglePID(PID_Coefs coefs);
    void updateSpeedPID(PID_Coefs coefs);

    void requestManualSpeeds();
    void requestJoystickSpeeds();
    void updateManualSpeeds(Speeds speeds);
    void updateJoystickSpeeds(Speeds speeds);

private:
    Ui::ConfigurationWindow *ui;
};

#endif // CONFIGURATIONWINDOW_H
