#include "bluetoothcommunicator.h"
#include <QtDebug>

// Communication signs - robot -> controller
#define TELEMETRY_SIGN          0b10000001
#define ANGLE_PID_COEFS_SIGN    0b10000010
#define SPEED_PID_COEFS_SIGN    0b10000011
#define MANUAL_SPEEDS_SIGN      0b10000100
#define JOYSTICK_SPEEDS_SIGN    0b10000101
#define MESSAGE_SIGN            0b10000110

// Communication signs - controller -> robot
#define GET_ANGLE_PID_COEFS_SIGN    0x00
#define GET_SPEED_PID_COEFS_SIGN    0x01
#define STOP_ROBOT                  0x02
#define RESTART_ROBOT               0x03
#define START_ROBOT                 0x04
#define SET_ANGLE_PID_COEFS_SIGN    0x05
#define SET_SPEED_PID_COEFS_SIGN    0x06
#define GET_MANUAL_SPEED            0x07
#define GET_JOYSTICK_SPEED          0x08
#define SET_MANUAL_SPEED            0x09
#define SET_JOYSTICK_SPEED          0x0A
#define SET_MANUAL_STOP             0x0B
#define SET_MANUAL_FWD              0x0C
#define SET_MANUAL_BWD              0x0D
#define SET_MANUAL_LEFT             0x0E
#define SET_MANUAL_RIGHT            0x0F
#define SET_JOYSTICK_CONTROL        0x10

// Sending drive commands period [ms]
#define SEND_COMMANDS_PERIOD 250

// Helper
void clearMessageData(MessageStructure &message)
{
    message.data[0] = 0.0;
    message.data[1] = 0.0;
    message.data[2] = 0.0;
}

BluetoothCommunicator::BluetoothCommunicator()
{
    this->timer = new QTimer(this);
    this->requested_robot_state = (RequestedRobotState){
            .state = NONE_REQUESTED,
            .joystick_driving_speed = 0.0,
            .joystick_turning_speed = 0.0,
};
    this->launched = false;

    connect(this->timer, SIGNAL(timeout()), this, SLOT(sendDriveCommand()));
}

void BluetoothCommunicator::parseReceivedBuffer(QByteArray buffer)
{
    if (buffer.size() < 1)
    {
        this->messageToLog("Odebrano pusty bufor");
        return;
    }
    switch ((uint8_t)buffer[0] & 0b10111111) // 7th bit for state
    {
        case TELEMETRY_SIGN:
    {
        //this->messageToLog("Odebrano telemetrie");
        if ((uint)buffer.size() != sizeof(Telemetry) + 1)
        {
            this->messageToLog("Telemetria niekompletna");
            return;
        }
        Telemetry new_telemetry;
        memcpy(&new_telemetry, buffer.constData() + 1, sizeof(Telemetry));
        if ((uint8_t)buffer[0] & 0b01000000) this->launched = true; else this->launched = false;
        emit parsedTelemetry(new_telemetry);
        break;

    }
    case ANGLE_PID_COEFS_SIGN:
    {
        qDebug() << "Odebrano wsp. PID kąta";
        if(uint(buffer.size()) != sizeof(PID_Coefs) + 1)
        {
            this->messageToLog("Wsp. PID kąta niekompletne");
            return;
        }
        PID_Coefs coefs;
        memcpy(&coefs, buffer.constData() + 1, sizeof(PID_Coefs));
        emit parsedAnglePID(coefs);
        break;
    }
    case SPEED_PID_COEFS_SIGN:
    {
        this->messageToLog("Odebrano wsp. PID prędkości");
        if(uint(buffer.size()) != sizeof(PID_Coefs) + 1)
        {
            this->messageToLog("Wsp. PID prędkości niekompletne");
            return;
        }
        PID_Coefs coefs;
        memcpy(&coefs, buffer.constData() + 1, sizeof(PID_Coefs));
        emit parsedSpeedPID(coefs);
        break;
    }
    case MANUAL_SPEEDS_SIGN:
    {
        this->messageToLog("Odebrano manualne prędkości");
        if(uint(buffer.size()) != sizeof(Speeds) + 1)
        {
            this->messageToLog("Manualne prędkości niekompletne");
        }
        Speeds speeds;
        memcpy(&speeds, buffer.constData() + 1, sizeof (Speeds));
        emit parsedManualSpeeds(speeds);
        break;
    }
    case JOYSTICK_SPEEDS_SIGN:
    {
        this->messageToLog("Odebrano joystickowe prędkości");
        if(uint(buffer.size()) != sizeof(Speeds) + 1)
        {
            this->messageToLog("Joystickowe prędkości niekompletne");
        }
        Speeds speeds;
        memcpy(&speeds, buffer.constData() + 1, sizeof (Speeds));
        emit parsedJoystickSpeeds(speeds);
        break;
    }
    case MESSAGE_SIGN:
    {
        this->messageToLog("Odebrano wiadomość");
        buffer.remove(0,1);
        QString message = QString(buffer);
        emit parsedMessage(message);
        break;

    }
    default:
    {
        this->messageToLog("Otrzymano błędny bufor");
        break;
    }
    }

}

void BluetoothCommunicator::requestAnglePID()
{
    MessageStructure message;
    message.sign = GET_ANGLE_PID_COEFS_SIGN;
    message.data[0] = 0.;
    message.data[1] = 0.;
    message.data[2] = 0.;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::requestSpeedPID()
{
    MessageStructure message;
    message.sign = GET_SPEED_PID_COEFS_SIGN;
    message.data[0] = 0.;
    message.data[1] = 0.;
    message.data[2] = 0.;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::updateAnglePID(PID_Coefs coefs)
{
    MessageStructure message;
    message.sign = SET_ANGLE_PID_COEFS_SIGN;
    message.data[0] = coefs.Kp;
    message.data[1] = coefs.Ki;
    message.data[2] = coefs.Kd;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::updateSpeedPID(PID_Coefs coefs)
{
    MessageStructure message;
    message.sign = SET_SPEED_PID_COEFS_SIGN;
    message.data[0] = coefs.Kp;
    message.data[1] = coefs.Ki;
    message.data[2] = coefs.Kd;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::requestManualSpeeds()
{
    MessageStructure message;
    message.sign = GET_MANUAL_SPEED;
    message.data[0] = 0.;
    message.data[1] = 0.;
    message.data[2] = 0.;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::requestJoystickSpeeds()
{
    MessageStructure message;
    message.sign = GET_JOYSTICK_SPEED;
    message.data[0] = 0.;
    message.data[1] = 0.;
    message.data[2] = 0.;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::updateManualSpeeds(Speeds speeds)
{
    MessageStructure message;
    message.sign = SET_MANUAL_SPEED;
    message.data[0] = speeds.driving_speed;
    message.data[1] = speeds.turning_speed;
    message.data[2] = 0.;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::updateJoystickSpeeds(Speeds speeds)
{
    MessageStructure message;
    message.sign = SET_JOYSTICK_SPEED;
    message.data[0] = speeds.driving_speed;
    message.data[1] = speeds.turning_speed;
    message.data[2] = 0.;
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::prepareMessageToSend(MessageStructure message)
{
    char byte_message[sizeof(MessageStructure)];
    memcpy(byte_message, &message, sizeof(MessageStructure));
    QByteArray qbyte_array = QByteArray(byte_message, sizeof(MessageStructure));
    emit messageToSend(qbyte_array);
}


void BluetoothCommunicator::startSendingDriveCommands()
{
    this->timer->start(SEND_COMMANDS_PERIOD);
}

void BluetoothCommunicator::stopSendingDriveCommands()
{
    this->timer->stop();
}

void BluetoothCommunicator::sendDriveCommand()
{
    qDebug() << "Sending drive command";
    if (this->launched == false)
    {
        qDebug() << "Robot not launched";
        return;
    }
    MessageStructure message;
    switch (this->requested_robot_state.state)
    {
    case NONE_REQUESTED:
    {
        return;
    }
    case MANUAL_FWD:
    {
        message.sign = SET_MANUAL_FWD;
        clearMessageData(message);
        break;
    }
    case MANUAL_BWD:
    {
        message.sign = SET_MANUAL_BWD;
        clearMessageData(message);
        break;
    }
    case MANUAL_LEFT:
    {
        message.sign = SET_MANUAL_LEFT;
        clearMessageData(message);
        break;
    }
    case MANUAL_RIGHT:
    {
        message.sign = SET_MANUAL_RIGHT;
        clearMessageData(message);
        break;
    }
    case MANUAL_STOP:
    {
        message.sign = SET_MANUAL_STOP;
        clearMessageData(message);
        break;
    }
    case JOYSTICK_SPEED:
    {
        message.sign = SET_JOYSTICK_CONTROL;
        message.data[0] = this->requested_robot_state.joystick_driving_speed;
        message.data[1] = this->requested_robot_state.joystick_turning_speed;
        break;
    }
    }
    this->prepareMessageToSend(message);
}

void BluetoothCommunicator::updateRequestedRobotState(RequestedRobotState state)
{
    if (state.joystick_driving_speed > 1.0) state.joystick_driving_speed = 1.0;
    if (state.joystick_driving_speed < -1.0) state.joystick_driving_speed = -1.0;
    if (state.joystick_turning_speed > 1.0) state.joystick_driving_speed = 1.0;
    if (state.joystick_turning_speed < -1.0) state.joystick_driving_speed = -1.0;
    this->requested_robot_state = state;
}


void BluetoothCommunicator::startRobot()
{
    this->requested_robot_state.state = NONE_REQUESTED;
    MessageStructure message;
    message.sign = START_ROBOT;
    clearMessageData(message);
    this->prepareMessageToSend(message);
}
void BluetoothCommunicator::stopRobot()
{
    this->requested_robot_state.state = NONE_REQUESTED;
    MessageStructure message;
    message.sign = STOP_ROBOT;
    clearMessageData(message);
    this->prepareMessageToSend(message);

}
void BluetoothCommunicator::restartRobot()
{
    this->requested_robot_state.state = NONE_REQUESTED;
    MessageStructure message;
    message.sign = RESTART_ROBOT;
    clearMessageData(message);
    this->prepareMessageToSend(message);

}
