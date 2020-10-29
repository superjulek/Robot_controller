#ifndef MANUALSTEERINGWINDOW_H
#define MANUALSTEERINGWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_pushButtonReturn_clicked();

private:
    Ui::ManualSteeringWindow *ui;
};

#endif // MANUALSTEERINGWINDOW_H
