#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QTimer>
#include "CommEPSM.h"
#include "SerialPortLL.h"

class SerialPort : public QObject
{
    Q_OBJECT

    Q_PROPERTY(unsigned int portsNumber READ getPortsNumber WRITE setPortsNumber NOTIFY portsNumberChanged)
    Q_PROPERTY(QStringList portsList READ getPortsList WRITE setPortsList NOTIFY portsListChanged)
    Q_PROPERTY(bool openPortFlag READ getOpenPortFlag WRITE setOpenPortFlag NOTIFY openPortFlagChanged)
    Q_PROPERTY(bool connBMSFlag READ getConnBMSFlag WRITE setConnBMSFlag NOTIFY connBMSFlagChanged)
    Q_PROPERTY(bool dataReadyFlag READ getDataReadyFlag WRITE setDataReadyFlag NOTIFY dataReadyFlagChanged)
    Q_PROPERTY(bool txBlinkTrigger READ getTxBlinkTrigger WRITE setTxBlinkTrigger NOTIFY txBlinkTriggerChanged)
    Q_PROPERTY(bool rxBlinkTrigger READ getRxBlinkTrigger WRITE setRxBlinkTrigger NOTIFY rxBlinkTriggerChanged)
    Q_PROPERTY(QString openPortName READ getOpenPortName WRITE setOpenPortName NOTIFY openPortNameChanged)

public:
    explicit SerialPort(QObject *parent = nullptr);

    Q_INVOKABLE unsigned int scanSerialPorts(void);
    Q_INVOKABLE void openSerialPort(QString portName, bool autoScanSlotFlag);
    Q_INVOKABLE void closeSerialPort(void);
    Q_INVOKABLE void startAutoConnectionScan(void);
    Q_INVOKABLE void stopAutoConnectionScan(void);
    Q_INVOKABLE void requestCmdSend(quint8 byte, quint32 data, quint8 size);

    unsigned int getPortsNumber() const;
    void setPortsNumber(unsigned int sPortsNumber);
    QStringList getPortsList() const;
    void setPortsList(QStringList portsList);
    bool getOpenPortFlag(void) const;
    void setOpenPortFlag(bool openPortFlag);
    bool getConnBMSFlag() const;
    void setConnBMSFlag(bool connBMSFlag);
    bool getDataReadyFlag() const;
    void setDataReadyFlag(bool dataReadyFlag);
    bool getTxBlinkTrigger() const;
    void setTxBlinkTrigger(bool txBlinkTrigger);
    bool getRxBlinkTrigger() const;
    void setRxBlinkTrigger(bool rxBlinkTrigger);
    QString getOpenPortName() const;
    void setOpenPortName(QString openPortName);

private:
    void startBMSCommunication(void);
    void stopBMSCommunication(void);

signals:
    void resetQmlSPortSignal(void);
    void portsNumberChanged(unsigned int portsNumber);
    void portsListChanged(QStringList portsList);
    void openPortFlagChanged(bool openPortFlag);
    void connBMSFlagChanged(bool connBMSFlag);
    void dataReadyFlagChanged(bool dataReadyFlag);
    void txBlinkTriggerChanged(bool txBlinkTrigger);
    void rxBlinkTriggerChanged(bool rxBlinkTrigger);  
    void openPortNameChanged(QString openPortName);
    void writeDataSignal(QByteArray data);
    void openSerialPortSignal(QString portName);
    void closeSerialPortSignal(void);

private slots:
    void portReadDataSlot(QByteArray data);
    void portErrorSlot(void);
    void sendDataRequestSlot(void);
    void autoBMSConnectionSlot(void);
    void openSerialPortSlot(bool status);

public:
    CommEPSM commEPSM;

private:
    QTimer *cmdRqTimer = nullptr;
    QTimer *scanTimer = nullptr;
    QStringList *availablePortsList = nullptr;
    unsigned int availablePorts;
    bool portStatusFlag;
    bool connBMSStatusFlag;
    quint8 sendRqCmdCnt;
    quint8 autoScanPortIdx;
    quint8 autoScanFlag;
    quint8 connFlagUpdateIdx;
    bool dataReadyStatusFlag;
    bool txBlinkTriggerFlag;
    bool rxBlinkTriggerFlag;
    QString mOpenPortName;
    quint8 cmdByteBuff[32];
    quint16 cmdRegBuff[32];
    quint32 cmdDataBuff[32];
    quint8 cmdDataSizeBuff[32];
    quint8 cmdBuffIdxIn;
    quint8 cmdBuffIdxOut;
    SerialPortLL *serialPortLL;
    bool autoScanSlotActive;
};

#endif // SERIALPORT_H
