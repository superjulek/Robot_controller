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
private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonAngleRefresh_clicked();

    void on_pushButtonSpeedRefresh_clicked();

    void on_pushButtonSpeedSend_clicked();

    void on_pushButtonAngleSend_clicked();

signals:
    void requestAnglePID();
    void requestSpeedPID();
    void updateAnglePID(PID_Coefs coefs);
    void updateSpeedPID(PID_Coefs coefs);

private:
    Ui::ConfigurationWindow *ui;
};

#endif // CONFIGURATIONWINDOW_H
