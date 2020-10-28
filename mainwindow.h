#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonCloseConnection_clicked();
    void on_pushButtonSearch_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonStart_clicked();
    void captureDeviceProperties(const QBluetoothDeviceInfo &device);
    void searchingFinished();
    void connectionEstablished();
    void connectionInterrupted();
    void socketReadyToRead();
private:
    Ui::MainWindow *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothSocket *socket;
    void addToLogs(QString message);
    void sendMessageToDevice(QByteArray message);
};
#endif // MAINWINDOW_H
