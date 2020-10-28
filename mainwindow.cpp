#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>
#include "joypad.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(this->discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(captureDeviceProperties(QBluetoothDeviceInfo)));
    connect(this->discoveryAgent, SIGNAL(finished()),this, SLOT(searchingFinished()));
    connect(this->socket, SIGNAL(connected()),this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(disconnected()),this, SLOT(connectionInterrupted()));
    connect(this->socket, SIGNAL(readyRead()),this, SLOT(socketReadyToRead()));
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
void MainWindow::on_pushButtonStart_clicked()
{
    QByteArray ba;
    ba.resize(1);
    ba[0] = 0x2;
    this->sendMessageToDevice(ba);
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
    while(this->socket->canReadLine()) {
        QString line = this->socket->readLine();

        QString terminator = "\n";
        int pos = line.lastIndexOf(terminator);

        this->addToLogs(line.left(pos));
      }
}

void MainWindow::sendMessageToDevice(QByteArray message)
{
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

