#ifndef BLUETOOTHCOMMUNICATOR_H
#define BLUETOOTHCOMMUNICATOR_H

#include <QWidget>

#define TELEMETRY_SIGN 0x2a

struct Telemetry {
    float TargetAngle;
    float Angle;
    float TargetSpeed;
    float Speed;
    float Battery;
};

class BluetoothCommunicator : public QWidget
{
    Q_OBJECT
public:
    explicit BluetoothCommunicator();
    void parseReceivedBuffer(QByteArray buffer);
   private:
signals:
    void parsedTelemetry (Telemetry new_telemetry);
    void parsedMessage (QString message);
};

#endif // BLUETOOTHCOMMUNICATOR_H

