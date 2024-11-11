#ifndef COMMEPSM_H
#define COMMEPSM_H

#include <QObject>
#include <QTimer>
#include "CommCRC.h"
#include "LiveData.h"
#include "SettingsDataMaster.h"

class CommEPSM : public QObject
{
    Q_OBJECT
public:
    explicit CommEPSM(QObject *parent = nullptr);

    bool cmdRxHandler(QByteArray &data);
    QByteArray &sendRqProfileData(quint16 regAddr, quint8 rqReg);
    QByteArray &sendRqCommStatus(void);
    QByteArray &sendCommand(quint8 byte, quint32 data, quint8 size);
    QByteArray &sendCommandModbusWrite(quint8 byte, quint16 reg, quint32 data, quint8 size);
    uint8_t getCmdState(void);
    void resetCmdState(void);
    void resetProfileData(void);
    bool getDataReadyFlag(void);
    bool getRxBlinkFlag(void); 
    bool getCmdTxReadyFlag(void);

signals:
    void updateProfileLiveData(LiveData &liveData);
    void updateProfileSettingsDataMaster(SettingsDataMaster &settingsDataMaster);

private:
    quint16 convertData2BInvToValue(QByteArray &data, quint16 startIndex);
    quint16 convertData2BToValue(QByteArray &data, quint16 startIndex);
    quint32 convertData4BToValue(QByteArray &data, quint16 startIndex);

private slots:
    void conTimerCallback(void);

private:
    CommCRC commCRC;
    QByteArray *rxDataBuff = nullptr;
    QByteArray *txDataBuff = nullptr;
    bool rxCmdStatus;
    quint8 rxErrorCnt;
    quint8 cmdState;
    quint8 rqRegCount;
    bool dataReadyFlag;
    bool rxBlinkFlag;
    LiveData liveData;
    SettingsDataMaster settingsDataMaster;
    bool cmdTxReadyFlag;
    QTimer *conTimer = nullptr;
    bool conTimerFlag;
};

#endif // COMMEPSM_H
