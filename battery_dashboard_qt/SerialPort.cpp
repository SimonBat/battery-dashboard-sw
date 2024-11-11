#include <QSerialPortInfo>
#include <QDebug>
#include "SerialPort.h"

SerialPort::SerialPort(QObject *parent):
    QObject(parent),
    cmdRqTimer(new QTimer),
    scanTimer(new QTimer),
    availablePortsList(new QStringList()),
    portStatusFlag(false),
    connBMSStatusFlag(false),
    sendRqCmdCnt(0),
    autoScanPortIdx(0),
    connFlagUpdateIdx(0),
    dataReadyStatusFlag(false),
    txBlinkTriggerFlag(false),
    rxBlinkTriggerFlag(false),
    mOpenPortName("NONE"),
    cmdBuffIdxIn(0),
    cmdBuffIdxOut(0),
    serialPortLL(new SerialPortLL)
{
    connect(serialPortLL, SIGNAL(readyReadSignal(QByteArray)), this, SLOT(portReadDataSlot(QByteArray)));
    connect(serialPortLL, SIGNAL(errorOccurredSignal()),this, SLOT(portErrorSlot()));
    connect(this, SIGNAL(writeDataSignal(QByteArray)), serialPortLL, SLOT(writeDataSlot(QByteArray)));
    connect(this, SIGNAL(openSerialPortSignal(QString)), serialPortLL, SLOT(openPortStartSlot(QString)));
    connect(serialPortLL, SIGNAL(openPortEndSignal(bool)), this, SLOT(openSerialPortSlot(bool)));
    connect(this, SIGNAL(closeSerialPortSignal()), serialPortLL, SLOT(closePortSlot()));
    connect(cmdRqTimer, SIGNAL(timeout()), this, SLOT(sendDataRequestSlot()));
    connect(scanTimer, SIGNAL(timeout()), this, SLOT(autoBMSConnectionSlot()));
}

unsigned int SerialPort::scanSerialPorts(void)
{
    unsigned int items = 0;

    availablePortsList->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info:infos)
    {
        availablePortsList->append(info.portName());
        items++;
    }

    setPortsNumber(items);
    if(0 == availablePortsList->count()){availablePortsList->append("NONE");}
    emit resetQmlSPortSignal();

    return items;
}

void SerialPort::openSerialPort(QString portName, bool autoScanSlotFlag)
{
    setOpenPortName(portName);
    autoScanSlotActive = autoScanSlotFlag;
    emit openSerialPortSignal(portName);
}

void SerialPort::openSerialPortSlot(bool status)
{
    if(status)
    {
        setOpenPortFlag(true);
        startBMSCommunication();

        if(autoScanSlotActive){scanTimer->stop();}
    }
    else
    {
        setOpenPortFlag(false);
        stopBMSCommunication();

        if(autoScanSlotActive)
        {
            autoScanPortIdx++;
            if(autoScanPortIdx >= availablePorts){autoScanPortIdx = 0;}
            scanTimer->stop();
            scanTimer->start(1000);
        }
    }
}

void SerialPort::closeSerialPort(void)
{
    stopBMSCommunication();
    emit closeSerialPortSignal();
    setOpenPortFlag(false);
    setConnBMSFlag(false);
}

void SerialPort::startAutoConnectionScan(void)
{
    if(0 != availablePorts)
    {
        scanTimer->stop();
        autoScanFlag = 1;
        autoScanPortIdx = 0;
        openSerialPort(availablePortsList->at(autoScanPortIdx), true);
    }
    else{scanTimer->start(1000);}
}

void SerialPort::stopAutoConnectionScan(void)
{
    scanTimer->stop();
    closeSerialPort();
    autoScanFlag = 0;
}

void SerialPort::startBMSCommunication(void)
{
    setDataReadyFlag(false);
    commEPSM.resetCmdState();
    cmdRqTimer->start(50);
}

void SerialPort::stopBMSCommunication(void)
{
    cmdRqTimer->stop();
    setDataReadyFlag(false);
    setTxBlinkTrigger(false);
    setRxBlinkTrigger(false);
    commEPSM.resetCmdState();
}

void SerialPort::requestCmdSend(quint8 byte, quint32 data, quint8 size)
{
    cmdByteBuff[cmdBuffIdxIn&(32 - 1)] = byte;
    cmdDataBuff[cmdBuffIdxIn&(32 - 1)] = data;
    cmdDataSizeBuff[cmdBuffIdxIn&(32 - 1)] = size;
    cmdRegBuff[cmdBuffIdxIn&(32 - 1)] = 0x0000;
    cmdBuffIdxIn++;
}

unsigned int SerialPort::getPortsNumber(void) const
{
    return availablePorts;
}

void SerialPort::setPortsNumber(unsigned int sPortsNumber)
{
    if (availablePorts == sPortsNumber){ return; }

    availablePorts = sPortsNumber;
    emit portsNumberChanged(availablePorts);
}

QStringList SerialPort::getPortsList(void) const
{
    return *availablePortsList;
}

void SerialPort::setPortsList(QStringList portsList)
{
    if (*availablePortsList == portsList){ return; }

    *availablePortsList = portsList;
    emit portsListChanged(*availablePortsList);
}

bool SerialPort::getOpenPortFlag() const
{
    return portStatusFlag;
}

void SerialPort::setOpenPortFlag(bool openPortFlag)
{
    if (portStatusFlag == openPortFlag){ return; }

    portStatusFlag = openPortFlag;
    emit openPortFlagChanged(portStatusFlag);
}

bool SerialPort::getConnBMSFlag() const
{
    return connBMSStatusFlag;
}

void SerialPort::setConnBMSFlag(bool connBMSFlag)
{
    if (connBMSStatusFlag == connBMSFlag){ return; }

    connBMSStatusFlag = connBMSFlag;
    emit connBMSFlagChanged(connBMSStatusFlag);

    if(false == connBMSFlag)
    {
        commEPSM.resetCmdState();
        commEPSM.resetProfileData();
    }
}

void SerialPort::portReadDataSlot(QByteArray data)
{
    bool connFlag = commEPSM.cmdRxHandler(data);

    if(++connFlagUpdateIdx >= 20)
    {
        connFlagUpdateIdx = 0;
        setConnBMSFlag(connFlag);
    }

    if(connFlag){sendRqCmdCnt = 0;}

    setDataReadyFlag(commEPSM.getDataReadyFlag());
    setRxBlinkTrigger(commEPSM.getRxBlinkFlag());
}

void SerialPort::portErrorSlot(void)
{
    setConnBMSFlag(false);
    setDataReadyFlag(false);
    commEPSM.resetCmdState();
    sendRqCmdCnt = 0;
    closeSerialPort();

    if(autoScanFlag)
    {
        autoScanFlag = 0;
        scanTimer->stop();
        scanTimer->start(1000);
    }
}

void SerialPort::sendDataRequestSlot(void)
{
    quint8 cmdByte;
    quint32 cmdData;
    quint8 cmdDataType;
    quint16 cmdReg;

    if(commEPSM.getCmdTxReadyFlag())
    {
        if(0 != (cmdBuffIdxIn-cmdBuffIdxOut))
        {
            cmdByte = cmdByteBuff[cmdBuffIdxOut&(32 - 1)];
            cmdData = cmdDataBuff[cmdBuffIdxOut&(32 - 1)];
            cmdDataType = cmdDataSizeBuff[cmdBuffIdxOut&(32 - 1)];
            cmdReg = cmdRegBuff[cmdBuffIdxOut&(32 - 1)];
            cmdBuffIdxOut++;
            if(0x10 == cmdByte){emit writeDataSignal(commEPSM.sendCommandModbusWrite(cmdByte, cmdReg, cmdData, cmdDataType));}
            else{emit writeDataSignal(commEPSM.sendCommand(cmdByte, cmdData, cmdDataType));}
            setTxBlinkTrigger(true);
        }
        else
        {
            switch(commEPSM.getCmdState())
            {
            case 0:
                emit writeDataSignal(commEPSM.sendRqCommStatus());
                setTxBlinkTrigger(true);
                break;

            case 1:
                // Get profile Settings Master
                emit writeDataSignal(commEPSM.sendRqProfileData(1700, 68));
                setTxBlinkTrigger(true);
                break;

            case 2:
                // Get master profile live data
                emit writeDataSignal(commEPSM.sendRqProfileData(0, 37));
                setTxBlinkTrigger(true);
                break;

            case 3:
                // Get battery profile data
                emit writeDataSignal(commEPSM.sendRqProfileData(1380, 32));
                setTxBlinkTrigger(true);
                break;

            default: break;
            }

            setDataReadyFlag(commEPSM.getDataReadyFlag());
        }
    }

    // No response from BMS report connection error!
    if(++sendRqCmdCnt >= 20)
    {
        setConnBMSFlag(false);
        commEPSM.resetCmdState();
        sendRqCmdCnt = 0;
        cmdBuffIdxIn = 0;
        cmdBuffIdxOut = 0;

        if(autoScanFlag)
        {
            closeSerialPort();
            autoScanPortIdx++;
            if(autoScanPortIdx >= availablePorts)
            {
                autoScanPortIdx = 0;
                scanSerialPorts();
            }
            openSerialPort(availablePortsList->at(autoScanPortIdx),false);
        }
    }
}

void SerialPort::autoBMSConnectionSlot(void)
{
    scanTimer->stop();
    unsigned int commPorts = scanSerialPorts();

    if(0 != commPorts)
    {    
        autoScanFlag = 1;
        if(autoScanPortIdx >= availablePorts){autoScanPortIdx = 0;}
        openSerialPort(availablePortsList->at(autoScanPortIdx), true);
    }
    else
    {
        setOpenPortName("NONE");
        scanTimer->stop();
        scanTimer->start(1000);
    }
}

bool SerialPort::getDataReadyFlag() const
{
    return dataReadyStatusFlag;
}

void SerialPort::setDataReadyFlag(bool dataReadyFlag)
{
    if (dataReadyStatusFlag == dataReadyFlag){ return; }

    dataReadyStatusFlag = dataReadyFlag;
    emit dataReadyFlagChanged(dataReadyStatusFlag);
}

bool SerialPort::getTxBlinkTrigger() const
{
    return txBlinkTriggerFlag;
}

void SerialPort::setTxBlinkTrigger(bool txBlinkTrigger)
{
    if (txBlinkTriggerFlag == txBlinkTrigger){ return; }

    txBlinkTriggerFlag = txBlinkTrigger;
    emit txBlinkTriggerChanged(txBlinkTriggerFlag);
}

bool SerialPort::getRxBlinkTrigger() const
{
    return rxBlinkTriggerFlag;
}

void SerialPort::setRxBlinkTrigger(bool rxBlinkTrigger)
{
    if (rxBlinkTriggerFlag == rxBlinkTrigger){ return; }

    rxBlinkTriggerFlag = rxBlinkTrigger;
    emit rxBlinkTriggerChanged(rxBlinkTriggerFlag);
}

QString SerialPort::getOpenPortName() const
{
    return mOpenPortName;
}

void SerialPort::setOpenPortName(QString openPortName)
{
    if (mOpenPortName == openPortName){ return; }

    mOpenPortName = openPortName;
    emit openPortNameChanged(mOpenPortName);
}
