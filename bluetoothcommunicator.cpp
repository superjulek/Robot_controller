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
        memcpy(&(this->current_telemetry.TargetAngle), buffer.constData() + offsetof(Telemetry, TargetAngle) + 1, 4);
        memcpy(&(this->current_telemetry.Angle), buffer.constData() + offsetof(Telemetry, Angle) + 1, 4);
        qDebug() << "TA = " << this->current_telemetry.TargetAngle;
        qDebug() << "A = " << this->current_telemetry.Angle;

    }
}
