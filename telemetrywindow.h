#ifndef TELEMETRYWINDOW_H
#define TELEMETRYWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QElapsedTimer>

#include "bluetoothcommunicator.h"

namespace Ui {
class TelemetryWindow;
}

class TelemetryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelemetryWindow(QWidget *parent = nullptr);
    ~TelemetryWindow();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void parsedTelemetry(Telemetry new_telemetry);
private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonStartDump_clicked();

    void on_pushButtonStopDump_clicked();

private:
    Ui::TelemetryWindow *ui;
    QFile *file;
    bool file_opened = false;
    QElapsedTimer timer;
};


#endif // TELEMETRYWINDOW_H
