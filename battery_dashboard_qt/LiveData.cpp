#include "LiveData.h"

LiveData::LiveData(QObject *parent) : QObject(parent),
    masterCellVolt(new QVector<quint16>(16)),
    masterCellTemp(new QVector<qint16>(4)),
    masterBmsTemp(new QVector<qint16>(3)),
    masterMinCellVoltage(0),
    masterMaxCellVoltage(0),
    masterMinCellTemp(-32768),
    masterMaxCellTemp(-32768),
    masterMinBmsTemp(-32768),
    masterMaxBmsTemp(-32768),
    masterModuleVoltage(0),
    masterBmsState(0),
    masterBalancingBits(0),
    masterBalancingDuration(0),
    masterLifeTimeCounter(0),
    masterPeriphStatus(0),
    battVoltage(0),
    battMinCellVoltage(0),
    battMaxCellVoltage(0),
    battMinCellTemp(-32768),
    battMaxCellTemp(-32768),
    battMinBmsTemp(-32768),
    battMaxBmsTemp(-32768),
    battIntCurrent(0),
    battIntCurrentAvg(0),
    battExtCurrent(0),
    battExtCurrentAvg(0),
    battCurrent(0),
    battCurrentAvg(0),
    battStateOfCharge(0),
    battStateOfHealth(0),
    battAvailableEnergy(0),
    battMaxChgCurrent(0),
    battMaxDsgCurrent(0),
    battResVoltage(0),
    battSungrowStatus(0),
    battExceptionLStatus(0),
    battExceptionMStatus(0)
{
    // Fill the cell voltage with zeroes
    for(quint8 idx = 0; idx < 16; idx++){masterCellVolt->replace(idx, 0);}
    for(quint8 idx = 0; idx < 4; idx++){masterCellTemp->replace(idx, -32768);}
    for(quint8 idx = 0; idx < 3; idx++){masterBmsTemp->replace(idx, -32768);}
}
