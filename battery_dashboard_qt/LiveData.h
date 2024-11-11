#ifndef LIVEDATA_H
#define LIVEDATA_H

#include <QObject>

class LiveData : public QObject
{
    Q_OBJECT
public:
    explicit LiveData(QObject *parent = nullptr);

    QVector<quint16> *masterCellVolt;
    QVector<qint16> *masterCellTemp;
    QVector<qint16> *masterBmsTemp;
    quint16 masterMinCellVoltage;
    quint16 masterMaxCellVoltage;
    qint16 masterMinCellTemp;
    qint16 masterMaxCellTemp;
    qint16 masterMinBmsTemp;
    qint16 masterMaxBmsTemp;
    quint32 masterModuleVoltage;
    quint16 masterBmsState;
    quint16 masterBalancingBits;
    quint16 masterBalancingDuration;
    quint32 masterLifeTimeCounter;
    quint16 masterPeriphStatus;
    quint32 battVoltage;
    quint16 battMinCellVoltage;
    quint16 battMaxCellVoltage;
    qint16 battMinCellTemp;
    qint16 battMaxCellTemp;
    qint16 battMinBmsTemp;
    qint16 battMaxBmsTemp;
    qint32 battIntCurrent;
    qint32 battIntCurrentAvg;
    qint32 battExtCurrent;
    qint32 battExtCurrentAvg;
    qint32 battCurrent;
    qint32 battCurrentAvg;
    quint32 battStateOfCharge;
    quint16 battStateOfHealth;
    quint32 battAvailableEnergy;
    quint16 battMaxChgCurrent;
    quint16 battMaxDsgCurrent;
    quint32 battResVoltage;
    quint8 battSungrowStatus;
    quint16 battExceptionLStatus;
    quint16 battExceptionMStatus;

signals:
};

#endif // LIVEDATA_H
