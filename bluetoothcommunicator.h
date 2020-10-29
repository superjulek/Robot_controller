#ifndef BLUETOOTHCOMMUNICATOR_H
#define BLUETOOTHCOMMUNICATOR_H

#include <QWidget>

class BluetoothCommunicator
{
public:
    BluetoothCommunicator();
    void parseReceivedBuffer(QString buffer);
};

#endif // BLUETOOTHCOMMUNICATOR_H
