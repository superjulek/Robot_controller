#include "bluetoothcommunicator.h"
#include <QtDebug>

// Communication signs - robot -> controller
#define TELEMETRY_SIGN          0b10000001
#define ANGLE_PID_COEFS_SIGN    0b10000010
#define SPEED_PID_COEFS_SIGN    0b10000011

//Communication signs - controller -> robot
#define GET_ANGLE_PID_COEFS_SIGN    0x00
#define GET_SPEED_PID_COEFS_SIGN    0x01
#define STOP_SIGN                   0x02
#define START_SIGN                  0x03
#define RESTART_SIGN                0x04

BluetoothCommunicator::BluetoothCommunicator()
{

}

void BluetoothCommunicator::parseReceivedBuffer(QByteArray buffer)
{
    if (buffer.size() < 1)
    {
        qDebug() << "Odebrano pusty bufor";
        return;
    }
    switch ((uint8_t)buffer[0])
    {
        case TELEMETRY_SIGN:
    {
        qDebug() << "Odebrano telemetrie";
        if ((uint)buffer.size() != sizeof(Telemetry) + 1)
        {
            qDebug() << "Telemetria niekompletna";
            return;
        }
        Telemetry new_telemetry;
        memcpy(&new_telemetry, buffer.constData() + 1, sizeof(Telemetry));
        //qDebug() << "TA = " << new_telemetry.TargetAngle;
        //qDebug() << "A = " << new_telemetry.Angle;
        //qDebug() << "TS = " << new_telemetry.TargetSpeed;
        //qDebug() << "S = " << new_telemetry.Speed;
        //qDebug() << "B = " << new_telemetry.Battery;

        emit parsedTelemetry(new_telemetry);
        break;

    }
    case ANGLE_PID_COEFS_SIGN:
    {
        qDebug() << "Odebrano wsp. PID kąta";
        if(uint(buffer.size()) != sizeof(PID_Coefs) + 1)
        {
            qDebug() << "Wsp. PID kąta niekompletne";
            return;
        }
        PID_Coefs coefs;
        memcpy(&coefs, buffer.constData() + 1, sizeof(PID_Coefs));
        emit parsedAnglePID(coefs);
        break;
    }
    default:
    {
        QString message = QString(buffer);
        qDebug() << message;

        emit parsedMessage(message);
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

void BluetoothCommunicator::prepareMessageToSend(MessageStructure message)
{
    char byte_message[sizeof(MessageStructure)];
    memcpy(byte_message, &message, sizeof(MessageStructure));
    QByteArray qbyte_array = QByteArray(byte_message, sizeof(MessageStructure));
    emit messageToSend(qbyte_array);
}
