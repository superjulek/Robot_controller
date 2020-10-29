#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_pushButtonReturn_clicked();

private:
    Ui::ConfigurationWindow *ui;
};

#endif // CONFIGURATIONWINDOW_H
