#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "joypad.h"

#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    telemetry_window = new TelemetryWindow();
    configuration_window = new ConfigurationWindow();
    joystick_steering_window = new JoystickSteeringWindow();
    manual_steering_window = new ManualSteeringWindow();

    this->discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    this->bluetooth_communicator = new BluetoothCommunicator();

    connect(this->discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(captureDeviceProperties(QBluetoothDeviceInfo)));
    connect(this->discoveryAgent, SIGNAL(finished()),this, SLOT(searchingFinished()));

    connect(this->socket, SIGNAL(connected()),this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(disconnected()),this, SLOT(connectionInterrupted()));
    connect(this->socket, SIGNAL(readyRead()),this, SLOT(socketReadyToRead()));

    connect(this->bluetooth_communicator, SIGNAL(parsedTelemetry(Telemetry)), this, SLOT(parsedTelemetry(Telemetry)));
    connect(this->bluetooth_communicator, SIGNAL(parsedMessage(QString)), this, SLOT(parsedMessage(QString)));
    connect(this->bluetooth_communicator, SIGNAL(parsedTelemetry(Telemetry)), this->telemetry_window, SLOT(parsedTelemetry(Telemetry)));
    connect(this->bluetooth_communicator, SIGNAL(messageToSend(QByteArray)), this, SLOT(sendMessageToDevice(QByteArray)));

    connect(this->configuration_window, SIGNAL(requestAnglePID()), this->bluetooth_communicator, SLOT(requestAnglePID()));
    connect(this->bluetooth_communicator, SIGNAL(parsedAnglePID(PID_Coefs)), this->configuration_window, SLOT(parsedAnglePID(PID_Coefs)));
}

void MainWindow::on_pushButtonConnect_clicked()
{
    QString comboBoxQString = ui->comboBoxDevices->currentText();
    QStringList portList = comboBoxQString.split(" ");
    QString deviceAddres = portList.last();

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    this->socket->connectToService(QBluetoothAddress(deviceAddres),QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);
    this->addToLogs("Rozpoczęto łączenie z urządzeniem o nazwie: " + portList.first() + " i adresie: " + deviceAddres);

    this->addToLogs("Łączenie...");
}
void MainWindow::on_pushButtonCloseConnection_clicked()
{
    this->addToLogs("Rozłączanie...");
    this->socket->disconnectFromService();
}
void MainWindow::on_pushButtonSearch_clicked()
{
    this->addToLogs("Szukanie...");
    ui->comboBoxDevices->clear();
    ui->pushButtonSearch->setEnabled(false);
    this->discoveryAgent->start();
}
void MainWindow::on_pushButtonClear_clicked()
{
    ui->textEditLogs->clear();
    this->addToLogs("Wyczyszczono.");
}
void MainWindow::captureDeviceProperties(const QBluetoothDeviceInfo &device)
{
    ui->comboBoxDevices->addItem(device.name() + " " + device.address().toString());
}
void MainWindow::searchingFinished() {
    ui->pushButtonSearch->setEnabled(true);
}
void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + "\t" + message);
}
void MainWindow::connectionEstablished() {
  this->addToLogs("Połączenie ustanowione.");
}

void MainWindow::connectionInterrupted() {
  this->addToLogs("Połączenie przerwane.");
}

void MainWindow::socketReadyToRead() {
    this->addToLogs("Odczytuje dane.");
    QByteArray rbuff = this->socket->readAll();
    qDebug() << "Odczytano: " << rbuff << Qt::endl;
    this->bluetooth_communicator->parseReceivedBuffer(rbuff);
}

void MainWindow::sendMessageToDevice(QByteArray message)
{
    qDebug() << "Proba wyslania: " << message <<Qt::endl;
    if (this->socket->isOpen() && this->socket->isWritable())
    {
        this->addToLogs("Wysyłanie wiadomości: " + message);
        this->socket->write(message);
    }
    else
    {
        this->addToLogs("Nie można wysyłać!");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonTelemetry_clicked()
{
    this->telemetry_window->show();
}

void MainWindow::on_pushButtonSteeringJoystick_clicked()
{
    this->joystick_steering_window->show();
}

void MainWindow::on_pushButtonConfig_clicked()
{
    this->configuration_window->show();
}

void MainWindow::on_pushButtonSteeringManual_clicked()
{
    this->manual_steering_window->show();
}

void MainWindow::parsedTelemetry(Telemetry)
{
    this->addToLogs("Otrzymano telemetrie");
}

void MainWindow::parsedMessage(QString message)
{
    this->addToLogs((message));
}
