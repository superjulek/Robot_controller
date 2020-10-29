#ifndef TELEMETRYWINDOW_H
#define TELEMETRYWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_pushButtonReturn_clicked();

private:
    Ui::TelemetryWindow *ui;
};


#endif // TELEMETRYWINDOW_H
