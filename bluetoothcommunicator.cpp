#include "bluetoothcommunicator.h"
#include <QtDebug>

BluetoothCommunicator::BluetoothCommunicator()
{

}

void BluetoothCommunicator::parseReceivedBuffer(QByteArray buffer)
{
    qDebug() << sizeof(Telemetry);
    if (buffer.size() < 1)
    {
        qDebug() << "Odebrano pusty bufor";
        return;
    }
    if ((uint8_t)buffer[0] == TELEMETRY_SIGN)
    {
        qDebug() << "Odebrano telemetrie";
        if ((uint)buffer.size() != sizeof(Telemetry) + 1)
        {
            qDebug() << "Telemetria niekompletna";
            return;
        }
        Telemetry new_telemetry;
        memcpy(&new_telemetry, buffer.constData() + 1, sizeof(Telemetry));
        qDebug() << "TA = " << new_telemetry.TargetAngle;
        qDebug() << "A = " << new_telemetry.Angle;
        qDebug() << "TS = " << new_telemetry.TargetSpeed;
        qDebug() << "S = " << new_telemetry.Speed;
        qDebug() << "B = " << new_telemetry.Battery;

        emit parsedTelemetry(new_telemetry);

    }
    else
    {
        QString message = QString(buffer);
        qDebug() << message;

        emit parsedMessage(message);
    }
}
