#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>

#include <telemetrywindow.h>
#include <configurationwindow.h>
#include <joysticksteeringwindow.h>
#include <manualsteeringwindow.h>

#include "bluetoothcommunicator.h"

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
    void captureDeviceProperties(const QBluetoothDeviceInfo &device);
    void searchingFinished();
    void connectionEstablished();
    void connectionInterrupted();
    void socketReadyToRead();
    void on_pushButtonTelemetry_clicked();

    void on_pushButtonSteeringJoystick_clicked();

    void on_pushButtonConfig_clicked();

    void on_pushButtonSteeringManual_clicked();

    void parsedMessage(QString);
    void sendMessageToDevice(QByteArray message);

    void on_pushButtonClearCommunication_clicked();

    void messageToLog(QString message);

private:
    Ui::MainWindow *ui;
    TelemetryWindow *telemetry_window;
    ConfigurationWindow *configuration_window;
    JoystickSteeringWindow *joystick_steering_window;
    ManualSteeringWindow *manual_steering_window;

    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothSocket *socket;
    BluetoothCommunicator *bluetooth_communicator;
    void addToLogs(QString message);
    void addToCommunicationLogs(QString message);
};
#endif // MAINWINDOW_H
