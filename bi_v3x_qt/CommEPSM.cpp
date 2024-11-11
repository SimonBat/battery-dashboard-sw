#include <QDebug>
#include "CommEPSM.h"

CommEPSM::CommEPSM(QObject *parent) : QObject(parent),
    rxDataBuff(new QByteArray()),
    txDataBuff(new QByteArray()),
    rxCmdStatus(false),
    rxErrorCnt(0),
    cmdState(0),
    rqRegCount(0),
    dataReadyFlag(false),
    rxBlinkFlag(false),
    cmdTxReadyFlag(true),
    conTimer(new QTimer(this)),
    conTimerFlag(false)
{
    rxDataBuff->clear();
    txDataBuff->clear();
    connect(conTimer, SIGNAL(timeout()), this,SLOT(conTimerCallback()));
}

bool CommEPSM::cmdRxHandler(QByteArray &data)
{
    quint16 crcValue;

    rxDataBuff->append(data);

    if((22 == rxDataBuff->size()) && (char(0xAA) == rxDataBuff->at(0)) && \
        (char(0x05) == rxDataBuff->at(1)) && (0 == cmdState) && (cmdTxReadyFlag))
    {
        crcValue = commCRC.calculateBufferCRC(*rxDataBuff, quint16(rxDataBuff->size() - 2));

        if(crcValue == convertData2BInvToValue(*rxDataBuff, quint16(rxDataBuff->size() - 2)))
        {
            rxCmdStatus = true;
            rxErrorCnt = 0;
            if(char(0x01) == rxDataBuff->at(16)){cmdState = 1;}
            rxBlinkFlag = true;
        }
        else
        {
            if(rxCmdStatus){rxErrorCnt++;}
            else{rxErrorCnt = 0;}
        }

        cmdTxReadyFlag = true;
        conTimer->stop();
    }
    // Catch first ACK from BMS after the request was sent
    else if((rxDataBuff->size() == (rqRegCount * 2 + 5)) && (char(0xAA) == rxDataBuff->at(0)) && \
             (char(0x03) == rxDataBuff->at(1)) && (rxDataBuff->at(2) == char(rqRegCount * 2)) && (0 != cmdState) && (cmdTxReadyFlag))
    {
        crcValue = commCRC.calculateBufferCRC(*rxDataBuff, quint16(rxDataBuff->size() - 2));

        if(crcValue == convertData2BInvToValue(*rxDataBuff, quint16(rxDataBuff->size() - 2)))
        {
            rxCmdStatus = true;
            rxErrorCnt = 0;

            switch(cmdState)
            {
            case 1:
                settingsDataMaster.cellsInSeriesMod = rxDataBuff->at(4); // Reg 0 LSB
                settingsDataMaster.modulesInSeries = rxDataBuff->at(3); // Reg 0 MSB
                settingsDataMaster.cellsInSeriesBatt = convertData2BToValue(*rxDataBuff, 5);
                settingsDataMaster.overVoltageDetThreshold = convertData2BToValue(*rxDataBuff, 7);
                settingsDataMaster.underVoltageDetThreshold = convertData2BToValue(*rxDataBuff, 23);
                settingsDataMaster.dsgOverCurrentDetThreshold_1 = convertData2BToValue(*rxDataBuff, 27);
                settingsDataMaster.dsgOverCurrentDetThreshold_2 = convertData2BToValue(*rxDataBuff, 29);
                settingsDataMaster.chgOverCurrentDetThreshold_1 = convertData2BToValue(*rxDataBuff, 39);
                settingsDataMaster.chgOverCurrentDetThreshold_2 = convertData2BToValue(*rxDataBuff, 41);
                settingsDataMaster.overVoltageDetThreshold = convertData2BToValue(*rxDataBuff, 7);
                settingsDataMaster.overVoltageRecThreshold = convertData2BToValue(*rxDataBuff, 9);
                settingsDataMaster.fullyDsgVoltageDetThreshold = convertData2BToValue(*rxDataBuff, 19);
                settingsDataMaster.fullyDsgVoltageRecThreshold = convertData2BToValue(*rxDataBuff, 21);
                settingsDataMaster.underVoltageDetThreshold = convertData2BToValue(*rxDataBuff, 23);
                settingsDataMaster.underVoltageRecThreshold = convertData2BToValue(*rxDataBuff, 25);
                settingsDataMaster.dsgOverCurrentDetThreshold_1 = convertData2BToValue(*rxDataBuff, 27);
                settingsDataMaster.dsgOverCurrentDetThreshold_2 = convertData2BToValue(*rxDataBuff, 29);
                settingsDataMaster.dsgOverCurrentDetTmo_1 = rxDataBuff->at(32);
                settingsDataMaster.dsgOverCurrentDetTmo_2 = rxDataBuff->at(31);
                settingsDataMaster.regOverCurrentDetThreshold_1 = convertData2BToValue(*rxDataBuff, 33);
                settingsDataMaster.regOverCurrentDetThreshold_2 = convertData2BToValue(*rxDataBuff, 35);
                settingsDataMaster.regOverCurrentDetTmo_1 = rxDataBuff->at(38);
                settingsDataMaster.regOverCurrentDetTmo_2 = rxDataBuff->at(37);
                settingsDataMaster.chgOverCurrentDetThreshold_1 = convertData2BToValue(*rxDataBuff, 39);
                settingsDataMaster.chgOverCurrentDetThreshold_2 = convertData2BToValue(*rxDataBuff, 41);
                settingsDataMaster.chgOverCurrentDetTmo_1 = rxDataBuff->at(44);
                settingsDataMaster.chgOverCurrentDetTmo_2 = rxDataBuff->at(43);
                settingsDataMaster.cellOverTempDetThreshold = convertData2BToValue(*rxDataBuff, 45);
                settingsDataMaster.cellOverTempRecThreshold = convertData2BToValue(*rxDataBuff, 47);
                settingsDataMaster.cellChgUnderTempDetThreshold = convertData2BToValue(*rxDataBuff, 49);
                settingsDataMaster.cellChgUnderTempRecThreshold = convertData2BToValue(*rxDataBuff, 51);
                settingsDataMaster.cellUnderTempDetThreshold = convertData2BToValue(*rxDataBuff, 53);
                settingsDataMaster.cellUnderTempRecThreshold = convertData2BToValue(*rxDataBuff, 55);
                settingsDataMaster.cellDiscDetThreshold = convertData2BToValue(*rxDataBuff, 57);
                settingsDataMaster.cellDiscDetTmo = rxDataBuff->at(60);
                settingsDataMaster.cellConnDetThreshold = convertData2BToValue(*rxDataBuff, 61);
                settingsDataMaster.cellConnDetTmo = rxDataBuff->at(64);
                settingsDataMaster.exceptionRecoveryTmo = convertData2BToValue(*rxDataBuff, 65);
                settingsDataMaster.fullyChgVoltageDetThreshold = convertData2BToValue(*rxDataBuff, 11);
                settingsDataMaster.fullyChgVoltageRecThreshold = convertData2BToValue(*rxDataBuff, 13);
                settingsDataMaster.fullyChgVoltageTolerance = convertData2BToValue(*rxDataBuff, 15);
                settingsDataMaster.fullyChgSwitchCtrlDisable = rxDataBuff->at(18);
                settingsDataMaster.fullyDsgSwitchCtrlDisable = rxDataBuff->at(17);
                settingsDataMaster.aiInHighThreshold = convertData2BToValue(*rxDataBuff, 67);
                settingsDataMaster.aiInLowThreshold = convertData2BToValue(*rxDataBuff, 69);
                settingsDataMaster.extOutputOCTmo = convertData2BToValue(*rxDataBuff, 75);
                settingsDataMaster.extOutputOCRecoveryTmo = convertData2BToValue(*rxDataBuff, 77);
                settingsDataMaster.extNtcSensorType = rxDataBuff->at(80);
                settingsDataMaster.extNtcSensorEnStatus = rxDataBuff->at(79);
                settingsDataMaster.extCurrentSensorType = rxDataBuff->at(82);
                settingsDataMaster.extCurrentSensorInvert = rxDataBuff->at(81);
                settingsDataMaster.currentAvgLevel = rxDataBuff->at(84);
                settingsDataMaster.switchDiagnosticsDisable = rxDataBuff->at(83);
                settingsDataMaster.operatingMode = rxDataBuff->at(86);
                settingsDataMaster.masterSlaveCommMode = rxDataBuff->at(85);
                settingsDataMaster.dpDsgSwitchType = rxDataBuff->at(88);
                settingsDataMaster.dpChgSwitchType = rxDataBuff->at(87);
                settingsDataMaster.spSwitchType = rxDataBuff->at(90);
                settingsDataMaster.spSwitchMonitorType = rxDataBuff->at(89);
                settingsDataMaster.preDsgSwitchType = rxDataBuff->at(92);
                settingsDataMaster.preDsgSwitchDuration = rxDataBuff->at(91);
                settingsDataMaster.ignitionType = rxDataBuff->at(94);
                settingsDataMaster.chgDetectionType = rxDataBuff->at(96);
                settingsDataMaster.chgEventsDisable = rxDataBuff->at(95);
                settingsDataMaster.chgIntDetectionHighThreshold = rxDataBuff->at(98);
                settingsDataMaster.chgIntDetectionLowThreshold = rxDataBuff->at(97);
                settingsDataMaster.dsgDetectionType = rxDataBuff->at(100);
                settingsDataMaster.dsgIntDetectionThreshold = rxDataBuff->at(99);
                settingsDataMaster.chargerType = rxDataBuff->at(102);
                settingsDataMaster.continuousBalancingEnable = rxDataBuff->at(101);
                settingsDataMaster.earlyBalancingThreshold = convertData2BToValue(*rxDataBuff, 103);
                settingsDataMaster.cellsAllowedDisbalance = convertData2BToValue(*rxDataBuff, 105);
                settingsDataMaster.chgCompleteCurrent = convertData2BToValue(*rxDataBuff, 107);
                settingsDataMaster.chargerConnectionTmo = rxDataBuff->at(110);
                settingsDataMaster.loadConnectionTmo = rxDataBuff->at(109);
                settingsDataMaster.batteryCapacity = convertData4BToValue(*rxDataBuff, 111);
                settingsDataMaster.stateOfCharge = convertData2BToValue(*rxDataBuff, 115);
                settingsDataMaster.stateOfHealth = convertData2BToValue(*rxDataBuff, 117);
                settingsDataMaster.sh10rtBattNominalEnergy = convertData4BToValue(*rxDataBuff, 119);
                settingsDataMaster.sh10rtBattSerialModules = rxDataBuff->at(124);
                settingsDataMaster.enMaxCurrentCtrl = rxDataBuff->at(123);
                settingsDataMaster.masterCellVoltCheckDisable = rxDataBuff->at(126);
                settingsDataMaster.masterCellTempCheckDisable = rxDataBuff->at(125);
                settingsDataMaster.cellResistance = convertData2BToValue(*rxDataBuff, 127);
                settingsDataMaster.extModuleType = rxDataBuff->at(130);
                settingsDataMaster.ecsLowChSensitivity = convertData2BToValue(*rxDataBuff, 131);
                settingsDataMaster.ecsHighChSensitivity = convertData2BToValue(*rxDataBuff, 133);
                settingsDataMaster.icsSensitivity = convertData2BToValue(*rxDataBuff, 135);
                settingsDataMaster.dsgCompleteCurrent = convertData2BToValue(*rxDataBuff, 137);
                emit updateProfileSettingsDataMaster(settingsDataMaster);

                cmdState = 2;
                rxBlinkFlag = true;
                break;

            case 2:
                for(quint8 idx=0; idx<16; idx++){liveData.masterCellVolt->replace(idx,convertData2BToValue(*rxDataBuff, (idx * 2 + 3)));}
                for(quint8 idx=0; idx<4; idx++){liveData.masterCellTemp->replace(idx,convertData2BToValue(*rxDataBuff, (idx * 2 + 35)));}
                for(quint8 idx=0; idx<3; idx++){liveData.masterBmsTemp->replace(idx,convertData2BToValue(*rxDataBuff, (idx * 2 + 43)));}
                liveData.masterMinCellVoltage = convertData2BToValue(*rxDataBuff, 49);
                liveData.masterMaxCellVoltage = convertData2BToValue(*rxDataBuff, 51);
                liveData.masterMinCellTemp = convertData2BToValue(*rxDataBuff, 53);
                liveData.masterMaxCellTemp = convertData2BToValue(*rxDataBuff, 55);
                liveData.masterMinBmsTemp = convertData2BToValue(*rxDataBuff, 57);
                liveData.masterMaxBmsTemp = convertData2BToValue(*rxDataBuff, 59);
                liveData.masterModuleVoltage = convertData4BToValue(*rxDataBuff, 61);
                liveData.masterBmsState = convertData2BToValue(*rxDataBuff, 65);
                liveData.masterBalancingBits = convertData2BToValue(*rxDataBuff, 67);
                liveData.masterBalancingDuration = convertData2BToValue(*rxDataBuff, 69);
                liveData.masterLifeTimeCounter = convertData4BToValue(*rxDataBuff, 71);
                liveData.masterPeriphStatus = convertData2BToValue(*rxDataBuff, 75);
                emit updateProfileLiveData(liveData);
                cmdState = 3;
                rxBlinkFlag = true;
                break;

            case 3:
                liveData.battVoltage = convertData4BToValue(*rxDataBuff, 3);
                liveData.battMinCellVoltage = convertData2BToValue(*rxDataBuff, 7);
                liveData.battMaxCellVoltage = convertData2BToValue(*rxDataBuff, 9);
                liveData.battMinCellTemp = convertData2BToValue(*rxDataBuff, 11);
                liveData.battMaxCellTemp = convertData2BToValue(*rxDataBuff, 13);
                liveData.battMinBmsTemp = convertData2BToValue(*rxDataBuff, 15);
                liveData.battMaxBmsTemp = convertData2BToValue(*rxDataBuff, 17);
                liveData.battIntCurrent = convertData4BToValue(*rxDataBuff, 19);
                liveData.battIntCurrentAvg = convertData4BToValue(*rxDataBuff, 23);
                liveData.battExtCurrent = convertData4BToValue(*rxDataBuff, 27);
                liveData.battExtCurrentAvg = convertData4BToValue(*rxDataBuff, 31);
                liveData.battCurrent = convertData4BToValue(*rxDataBuff, 35);
                liveData.battCurrentAvg = convertData4BToValue(*rxDataBuff, 39);
                liveData.battStateOfCharge = convertData4BToValue(*rxDataBuff, 43);
                liveData.battStateOfHealth = convertData2BToValue(*rxDataBuff, 47);
                liveData.battAvailableEnergy = convertData4BToValue(*rxDataBuff, 49);
                liveData.battMaxChgCurrent = convertData2BToValue(*rxDataBuff, 53);
                liveData.battMaxDsgCurrent = convertData2BToValue(*rxDataBuff, 55);
                liveData.battResVoltage = convertData4BToValue(*rxDataBuff, 57);
                liveData.battSungrowStatus = rxDataBuff->at(62);
                liveData.battExceptionLStatus = convertData2BToValue(*rxDataBuff, 63);
                liveData.battExceptionMStatus = convertData2BToValue(*rxDataBuff, 65);
                emit updateProfileLiveData(liveData);

                cmdState = 1;
                dataReadyFlag = true;
                rxBlinkFlag = true;
                break;
            }
        }
        else
        {
            if(rxCmdStatus){rxErrorCnt++;}
            else{rxErrorCnt = 0;}
        }

        rxDataBuff->clear();
        cmdTxReadyFlag = true;
        conTimer->stop();
    }
    else if((rxDataBuff->size() < (rqRegCount * 2 + 5)) && (char(0xAA) == rxDataBuff->at(0)) && (0 != cmdState) && (cmdTxReadyFlag))
    {
        rxCmdStatus = true;
        conTimer->stop();
    }
    // ACK/NACK to command
    else if(((5 == rxDataBuff->size()) || (6 == rxDataBuff->size())) && (char(0xAA) == rxDataBuff->at(0)) && \
             (char(0x11) != rxDataBuff->at(1)) && (char(0x12) != rxDataBuff->at(1)) && (!cmdTxReadyFlag))
    {
        cmdTxReadyFlag = true;
        conTimer->stop();
    }
    // Modbus write command
    else if((8 == rxDataBuff->size()) && (char(0xAA) == rxDataBuff->at(0)) && (char(0x10) == rxDataBuff->at(1)) && (!cmdTxReadyFlag))
    {
        cmdTxReadyFlag = true;
        conTimer->stop();
    }
    else{rxBlinkFlag = false;}

    if((!cmdTxReadyFlag) && (!conTimerFlag))
    {
        rxCmdStatus = true;
        cmdTxReadyFlag = true;
    }

    return rxCmdStatus;
}

QByteArray &CommEPSM::sendRqProfileData(quint16 regAddr, quint8 rqReg)
{
    rxCmdStatus = false;
    rxErrorCnt = 0;
    conTimerFlag = true;
    conTimer->start(100);
    rxDataBuff->clear();
    txDataBuff->clear();
    txDataBuff->append(char(0xAA));
    txDataBuff->append(char(0x03));
    txDataBuff->append(char((regAddr >> 8) & 0xFF));
    txDataBuff->append(char(regAddr & 0xFF));
    txDataBuff->append(char(0x00));
    txDataBuff->append(char(rqReg));
    uint16_t crcValue = commCRC.calculateBufferCRC(*txDataBuff, quint16(txDataBuff->size()));
    txDataBuff->append(char(crcValue >> 0 & 0xFF));
    txDataBuff->append(char(crcValue >> 8 & 0xFF));
    rqRegCount = rqReg;

    return *txDataBuff;
}

QByteArray &CommEPSM::sendRqCommStatus(void)
{
    rxCmdStatus = false;
    rxErrorCnt = 0;
    conTimerFlag = true;
    conTimer->start(100);
    rxDataBuff->clear();
    txDataBuff->clear();
    txDataBuff->append(char(0xAA));
    txDataBuff->append(char(0x05));
    uint16_t crcValue = commCRC.calculateBufferCRC(*txDataBuff, quint16(txDataBuff->size()));
    txDataBuff->append(char(crcValue >> 0 & 0xFF));
    txDataBuff->append(char(crcValue >> 8 & 0xFF));

    return *txDataBuff;
}

QByteArray &CommEPSM::sendCommand(quint8 byte, quint32 data, quint8 size)
{
    cmdTxReadyFlag = false;
    conTimerFlag = true;
    conTimer->start(100);
    rxDataBuff->clear();
    txDataBuff->clear();
    txDataBuff->append(char(0xAA));
    txDataBuff->append(char(byte));

    switch(size)
    {   
    case(1):
        txDataBuff->append(char(data & 0xFF));
        break;

    case(2):
        txDataBuff->append(char(data & 0xFF));
        txDataBuff->append(char((data >> 8) & 0xFF));
        break;

    case(3):
        txDataBuff->append(char(data & 0xFF));
        txDataBuff->append(char((data >> 8) & 0xFF));
        txDataBuff->append(char((data >> 16) & 0xFF));
        break;

    case(4):
        txDataBuff->append(char(data & 0xFF));
        txDataBuff->append(char((data >> 8) & 0xFF));
        txDataBuff->append(char((data >> 16) & 0xFF));
        txDataBuff->append(char((data >> 24) & 0xFF));
        break;

    default:
        break;
    }

    uint16_t crcValue = commCRC.calculateBufferCRC(*txDataBuff, quint16(txDataBuff->size()));
    txDataBuff->append(char(crcValue >> 0 & 0xFF));
    txDataBuff->append(char(crcValue >> 8 & 0xFF));

    return *txDataBuff;
}

QByteArray &CommEPSM::sendCommandModbusWrite(quint8 byte, quint16 reg, quint32 data, quint8 size)
{
    cmdState = 1;
    cmdTxReadyFlag = false;
    conTimerFlag = true;
    conTimer->start(100);
    rxDataBuff->clear();
    txDataBuff->clear();
    txDataBuff->append(char(0xAA));
    txDataBuff->append(char(byte));
    txDataBuff->append(char((reg >> 8) & 0xFF));
    txDataBuff->append(char(reg & 0xFF));
    txDataBuff->append(char(0x00));
    txDataBuff->append(char(size / 2));
    txDataBuff->append(char(size));

    switch(size)
    {
    case(2):
        txDataBuff->append(char((data >> 8) & 0xFF));
        txDataBuff->append(char(data & 0xFF));
        break;

    case(4):
        txDataBuff->append(char((data >> 8) & 0xFF));
        txDataBuff->append(char(data & 0xFF));
        txDataBuff->append(char((data >> 24) & 0xFF));
        txDataBuff->append(char((data >> 16) & 0xFF));
        break;

    default:
        break;
    }

    uint16_t crcValue = commCRC.calculateBufferCRC(*txDataBuff, quint16(txDataBuff->size()));
    txDataBuff->append(char(crcValue >> 0 & 0xFF));
    txDataBuff->append(char(crcValue >> 8 & 0xFF));

    return *txDataBuff;
}

quint8 CommEPSM::getCmdState(void)
{
    return cmdState;
}

void CommEPSM::resetCmdState(void)
{
    cmdState = 0;
}

quint16 CommEPSM::convertData2BInvToValue(QByteArray &data, quint16 startIndex)
{
    quint16 value = 0;

    value |= data[startIndex + 1] & 0xFF;
    value <<= 8;
    value |= data[startIndex] & 0xFF;

    return value;
}

quint16 CommEPSM::convertData2BToValue(QByteArray &data, quint16 startIndex)
{
    quint16 value = 0;

    value |= data[startIndex] & 0xFF;
    value <<= 8;
    value |= data[startIndex + 1] & 0xFF;

    return value;
}

quint32 CommEPSM::convertData4BToValue(QByteArray &data, quint16 startIndex)
{
    quint32 value = 0;

    value |= data[startIndex + 2] & 0xFF;
    value <<= 8;
    value |= data[startIndex + 3] & 0xFF;
    value <<= 8;
    value |= data[startIndex] & 0xFF;
    value <<= 8;
    value |= data[startIndex + 1] & 0xFF;

    return value;
}

void CommEPSM::resetProfileData()
{
    dataReadyFlag = false;
    rxBlinkFlag = false;
    conTimerFlag = false;
    cmdTxReadyFlag = true;
    settingsDataMaster.cellsInSeriesMod = 16;
    settingsDataMaster.overVoltageDetThreshold = 420;
    settingsDataMaster.underVoltageDetThreshold = 200;
    settingsDataMaster.dsgOverCurrentDetThreshold_1 = 150;
    settingsDataMaster.dsgOverCurrentDetThreshold_2 = 150;
    settingsDataMaster.chgOverCurrentDetThreshold_1 = 150;
    settingsDataMaster.chgOverCurrentDetThreshold_2 = 150;
    settingsDataMaster.batteryCapacity = 0;
    settingsDataMaster.stateOfCharge = 0x5555;
    settingsDataMaster.dpDsgSwitchType = 0;
    settingsDataMaster.dpChgSwitchType = 0;
    settingsDataMaster.spSwitchType = 0;
    settingsDataMaster.spSwitchMonitorType = 0;
    settingsDataMaster.ignitionType = 0;
    settingsDataMaster.preDsgSwitchType = 0;
    settingsDataMaster.preDsgSwitchDuration = 1;
    settingsDataMaster.chargerType = 0;
    settingsDataMaster.chgDetectionType = 0;
    settingsDataMaster.chgIntDetectionHighThreshold = 1;
    settingsDataMaster.chgIntDetectionLowThreshold = 1;
    settingsDataMaster.chargerConnectionTmo = 1;
    settingsDataMaster.loadConnectionTmo = 1;
    settingsDataMaster.earlyBalancingThreshold = 100;
    settingsDataMaster.cellsAllowedDisbalance = 5;
    settingsDataMaster.chgCompleteCurrent = 2;
    settingsDataMaster.dsgCompleteCurrent = 2;
    settingsDataMaster.dsgDetectionType = 0;
    settingsDataMaster.dsgIntDetectionThreshold = 5;
    settingsDataMaster.fullyChgVoltageDetThreshold = 120;
    settingsDataMaster.fullyChgVoltageRecThreshold = 120;
    settingsDataMaster.fullyChgVoltageTolerance = 0;
    settingsDataMaster.fullyChgSwitchCtrlDisable = 0;
    settingsDataMaster.fullyDsgSwitchCtrlDisable = 0;
    settingsDataMaster.aiInHighThreshold = 5;
    settingsDataMaster.aiInLowThreshold = 3;
    settingsDataMaster.extOutputOCTmo = 0;
    settingsDataMaster.extOutputOCRecoveryTmo = 0;
    settingsDataMaster.extNtcSensorType = 0;
    settingsDataMaster.extNtcSensorEnStatus = 0;
    settingsDataMaster.extCurrentSensorType = 0;
    settingsDataMaster.extCurrentSensorInvert = 0;
    settingsDataMaster.currentAvgLevel = 0;
    settingsDataMaster.switchDiagnosticsDisable = 0;
    settingsDataMaster.overVoltageDetThreshold = 420;
    settingsDataMaster.overVoltageRecThreshold = 420;
    settingsDataMaster.fullyDsgVoltageDetThreshold = 80;
    settingsDataMaster.fullyDsgVoltageRecThreshold = 80;
    settingsDataMaster.underVoltageDetThreshold = 200;
    settingsDataMaster.underVoltageRecThreshold = 200;
    settingsDataMaster.dsgOverCurrentDetThreshold_1 = 1;
    settingsDataMaster.dsgOverCurrentDetThreshold_2 = 1;
    settingsDataMaster.dsgOverCurrentDetTmo_1 = 0;
    settingsDataMaster.dsgOverCurrentDetTmo_2 = 0;
    settingsDataMaster.regOverCurrentDetThreshold_1 = 1;
    settingsDataMaster.regOverCurrentDetThreshold_2 = 1;
    settingsDataMaster.regOverCurrentDetTmo_1 = 0;
    settingsDataMaster.regOverCurrentDetTmo_2 = 0;
    settingsDataMaster.chgOverCurrentDetThreshold_1 = 1;
    settingsDataMaster.chgOverCurrentDetThreshold_2 = 1;
    settingsDataMaster.chgOverCurrentDetTmo_1 = 0;
    settingsDataMaster.chgOverCurrentDetTmo_2 = 0;
    settingsDataMaster.cellOverTempDetThreshold = 90;
    settingsDataMaster.cellOverTempRecThreshold = 90;
    settingsDataMaster.cellChgUnderTempDetThreshold = -40;
    settingsDataMaster.cellChgUnderTempRecThreshold = -40;
    settingsDataMaster.cellUnderTempDetThreshold = -40;
    settingsDataMaster.cellUnderTempRecThreshold = -40;
    settingsDataMaster.cellDiscDetThreshold = 5;
    settingsDataMaster.cellDiscDetTmo = 0;
    settingsDataMaster.cellConnDetThreshold = 5;
    settingsDataMaster.cellConnDetTmo = 0;
    settingsDataMaster.exceptionRecoveryTmo = 0;
    settingsDataMaster.chgEventsDisable = 0;
    settingsDataMaster.stateOfHealth = 0x5555;
    settingsDataMaster.sh10rtBattNominalEnergy = 9600;
    settingsDataMaster.sh10rtBattSerialModules = 3;
    settingsDataMaster.enMaxCurrentCtrl = 0;
    settingsDataMaster.masterCellVoltCheckDisable = 0;
    settingsDataMaster.masterCellTempCheckDisable = 0;
    settingsDataMaster.cellResistance = 0;
    settingsDataMaster.extModuleType = 0;
    settingsDataMaster.ecsLowChSensitivity = 0;
    settingsDataMaster.ecsHighChSensitivity = 0;
    settingsDataMaster.continuousBalancingEnable = 0;
    settingsDataMaster.icsSensitivity = 0;
    emit updateProfileSettingsDataMaster(settingsDataMaster);

    for(quint8 idx = 0; idx < 16; idx++){liveData.masterCellVolt->replace(idx, 0);}
    for(quint8 idx = 0; idx < 4; idx++){ liveData.masterCellTemp->replace(idx, -32768);}
    for(quint8 idx = 0; idx < 3; idx++){ liveData.masterBmsTemp->replace(idx, -32768);}
    liveData.masterMinCellVoltage = 0;
    liveData.masterMaxCellVoltage = 0;
    liveData.masterMinCellTemp = -32768;
    liveData.masterMaxCellTemp = -32768;
    liveData.masterMinBmsTemp = -32768;
    liveData.masterMaxBmsTemp = -32768;
    liveData.masterModuleVoltage = 0;
    liveData.masterBmsState = 0;
    liveData.masterBalancingBits = 0;
    liveData.masterBalancingDuration = 0;
    liveData.masterLifeTimeCounter = 0;
    liveData.masterPeriphStatus = 0;

    liveData.battVoltage = 0;
    liveData.battMinCellVoltage = 0;
    liveData.battMaxCellVoltage = 0;
    liveData.battMinCellTemp = -32768;
    liveData.battMaxCellTemp = -32768;
    liveData.battMinBmsTemp = -32768;
    liveData.battMaxBmsTemp = -32768;
    liveData.battIntCurrent = 0;
    liveData.battIntCurrentAvg = 0;
    liveData.battExtCurrent = 0;
    liveData.battExtCurrentAvg = 0;
    liveData.battCurrent = 0;
    liveData.battCurrentAvg = 0;
    liveData.battStateOfCharge = 0;
    liveData.battStateOfHealth = 0;
    liveData.battAvailableEnergy = 0;
    liveData.battMaxChgCurrent = 0;
    liveData.battMaxDsgCurrent = 0;
    liveData.battResVoltage = 0;
    liveData.battSungrowStatus = 0;
    liveData.battExceptionLStatus = 0;
    liveData.battExceptionMStatus = 0;
    emit updateProfileLiveData(liveData);
}

bool CommEPSM::getDataReadyFlag(void)
{
    return dataReadyFlag;
}

bool CommEPSM::getRxBlinkFlag(void)
{
    return rxBlinkFlag;
}

bool CommEPSM::getCmdTxReadyFlag(void)
{
    return cmdTxReadyFlag;
}

void CommEPSM::conTimerCallback(void)
{
    conTimer->stop();
    conTimerFlag = false;
}
