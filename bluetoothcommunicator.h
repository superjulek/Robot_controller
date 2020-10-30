#ifndef BLUETOOTHCOMMUNICATOR_H
#define BLUETOOTHCOMMUNICATOR_H

#include <QWidget>

#define TELEMETRY_SIGN 0x2a

struct Telemetry {
    float TargetAngle;
    float Angle;
};

class BluetoothCommunicator
{
public:
    BluetoothCommunicator();
    void parseReceivedBuffer(QByteArray buffer);
   private:
    Telemetry current_telemetry;
};

#endif // BLUETOOTHCOMMUNICATOR_H

