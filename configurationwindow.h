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
private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonAngleRefresh_clicked();

signals:
    void requestAnglePID();

private:
    Ui::ConfigurationWindow *ui;
};

#endif // CONFIGURATIONWINDOW_H
