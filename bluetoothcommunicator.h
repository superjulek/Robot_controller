#ifndef BLUETOOTHCOMMUNICATOR_H
#define BLUETOOTHCOMMUNICATOR_H

#include <QWidget>

struct Telemetry {
    float TargetAngle;
    float Angle;
    float TargetSpeed;
    float Speed;
    float Battery;
};

struct PID_Coefs {
    float Kp;
    float Ki;
    float Kd;
};

struct MessageStructure {
    quint32 sign;
    float data[3];
};

class BluetoothCommunicator : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothCommunicator();
    void parseReceivedBuffer(QByteArray buffer);

private:
    void prepareMessageToSend (MessageStructure message);

signals:
    void parsedTelemetry (Telemetry new_telemetry);
    void parsedMessage (QString message);
    void parsedAnglePID (PID_Coefs coefs);
    void parsedSpeedPID (PID_Coefs coefs);
    void messageToSend (QByteArray message);

public slots:
    void requestAnglePID();
    void requestSpeedPID();
    void updateAnglePID(PID_Coefs coefs);
    void updateSpeedPID(PID_Coefs coefs);
};

#endif // BLUETOOTHCOMMUNICATOR_H

