#ifndef BLUETOOTHCOMMUNICATOR_H
#define BLUETOOTHCOMMUNICATOR_H

#include <QWidget>
#include <QTimer>

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

struct Speeds {
    float driving_speed;
    float turning_speed;
};

struct MessageStructure {
    quint8 sign;
    float data[3];
}__packed;

enum RequestedStateEnum {
    NONE_REQUESTED,
    MANUAL_FWD,
    MANUAL_BWD,
    MANUAL_LEFT,
    MANUAL_RIGHT,
    MANUAL_STOP,
    JOYSTICK_SPEED,
};

struct RequestedRobotState {
    RequestedStateEnum state;
    float joystick_driving_speed; // -1 -> 1
    float joystick_turning_speed; // -1 -> 1
};

class BluetoothCommunicator : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothCommunicator();
    void parseReceivedBuffer(QByteArray buffer);

private:
    void prepareMessageToSend (MessageStructure message);
    QTimer *timer;
    bool launched;
    RequestedRobotState requested_robot_state;
private slots:
    void sendDriveCommand();

signals:
    void parsedTelemetry (Telemetry new_telemetry);
    void parsedMessage (QString message);
    void parsedAnglePID (PID_Coefs coefs);
    void parsedSpeedPID (PID_Coefs coefs);
    void parsedManualSpeeds (Speeds);
    void parsedJoystickSpeeds (Speeds);
    void messageToSend (QByteArray message);
    void messageToLog (QString message);

public slots:
    void requestAnglePID();
    void requestSpeedPID();
    void updateAnglePID(PID_Coefs coefs);
    void updateSpeedPID(PID_Coefs coefs);

    void requestManualSpeeds();
    void requestJoystickSpeeds();
    void updateManualSpeeds(Speeds);
    void updateJoystickSpeeds(Speeds);

    void startSendingDriveCommands();
    void stopSendingDriveCommands();
    void updateRequestedRobotState(RequestedRobotState);
    void startRobot();
    void stopRobot();
    void restartRobot();
};

#endif // BLUETOOTHCOMMUNICATOR_H

