#include "DataProfile.h"
#include <QDebug>

DataProfile::DataProfile(QObject *parent) : QObject(parent),
    pMasterCellVolt(new QVector<qreal>(16)),
    pMasterCellTemp(new QVector<qreal>(4)),
    pMasterBmsTemp(new QVector<qreal>(3)),
    pMasterMinCellVoltage(0),
    pMasterMaxCellVoltage(0),
    pMasterMinCellTemp(-32768),
    pMasterMaxCellTemp(-32768),
    pMasterMinBmsTemp(-32768),
    pMasterMaxBmsTemp(-32768),
    pMasterModuleVoltage(0),
    pMasterBmsState(0),
    pMasterBalancingBits(0),
    pMasterBalancingDuration(0),
    pMasterLifeTimeCounter(0),
    pMasterPeriphStatus(0),
    pBattVoltage(0),
    pBattMinCellVoltage(0),
    pBattMaxCellVoltage(0),
    pBattMinCellTemp(-32768),
    pBattMaxCellTemp(-32768),
    pBattMinBmsTemp(-32768),
    pBattMaxBmsTemp(-32768),
    pBattIntCurrent(0),
    pBattIntCurrentAvg(0),
    pBattExtCurrent(0),
    pBattExtCurrentAvg(0),
    pBattCurrent(0),
    pBattCurrentAvg(0),
    pBattStateOfCharge(0),
    pBattStateOfHealth(0),
    pBattAvailableEnergy(0),
    pBattMaxChgCurrent(0),
    pBattMaxDsgCurrent(0),
    pBattResVoltage(0),
    pBattSungrowStatus(0),
    pBattExceptionL(0),
    pBattExceptionM(0),
    psetCellsInSeriesMod(16),
    psetCellsInSeriesBatt(16),
    psetModulesInSeries(1),
    psetOverVoltageDetThreshold(4200),
    psetUnderVoltageDetThreshold(2000),
    psetSlOverVoltageDetThreshold(4200),
    psetSlUnderVoltageDetThreshold(2000),
    psetDsgOcDetThreshold(150),
    psetChgOcDetThreshold(150),
    psetOperatingMode(0),
    psetMasterSlaveCommMode(0),
    psetDpDsgSwitchType(0),
    psetDpChgSwitchType(0),
    psetSpSwitchType(0),
    psetSpSwitchMonitorType(0),
    psetPreDsgSwitchType(0),
    psetPreDsgSwitchDuration(1),
    psetIgnitionType(0),
    psetChgDetectionType(0),
    psetChgIntDetectionHighThreshold(1),
    psetChgIntDetectionLowThreshold(1),
    psetDsgDetectionType(0),
    psetDsgIntDetectionThreshold(5),
    psetChargerType(0),
    psetEarlyBalancingThs(100),
    psetCellsAllowedDisbalance(5),
    psetChgCompleteCurrent(2),
    psetDsgCompleteCurrent(2),
    psetChgConnectionTmo(1),
    psetDsgConnectionTmo(1),
    psetBatteryCapacity(0),
    psetStateOfCharge(0x5555),
    psetFullyChgVoltageDetThs(120),
    psetFullyChgVoltageRecThs(120),
    psetFullyChgVoltageTolerance(0),
    psetFullyChgSwitchCtrlDisable(0),
    psetAiInHighThreshold(5),
    psetAiInLowThreshold(3),
    psetExtOutputOCTmo(0),
    psetExtOutputOCRecTmo(0),
    psetExtNtcSensorType(0),
    psetExtNtcSensorEnStatus(0),
    psetExtCurrentSensorType(0),
    psetExtCurrentSensorInvert(0),
    psetCurrentAvgLevel(0),
    psetSwDiagnosticsDisable(0),
    epsetFullyDsgSwitchCtrlDisable(0),
    epsetOverVoltageDetThs(120),
    epsetOverVoltageRecThs(120),
    epsetFullyDsgVoltageDetThs(80),
    epsetFullyDsgVoltageRecThs(80),
    epsetUnderVoltageDetThs(80),
    epsetUnderVoltageRecThs(80),
    epsetDsgOverCurrentDetThs1(1),
    epsetDsgOverCurrentDetThs2(1),
    epsetDsgOverCurrentDetTmo1(0),
    epsetDsgOverCurrentDetTmo2(0),
    epsetRegOverCurrentDetThs1(1),
    epsetRegOverCurrentDetThs2(1),
    epsetRegOverCurrentDetTmo1(0),
    epsetRegOverCurrentDetTmo2(0),
    epsetChgOverCurrentDetThs1(1),
    epsetChgOverCurrentDetThs2(1),
    epsetChgOverCurrentDetTmo1(0),
    epsetChgOverCurrentDetTmo2(0),
    epsetCellOverTempDetThs(90),
    epsetCellOverTempRecThs(90),
    epsetCellChgUnderTempDetThs(-40),
    epsetCellChgUnderTempRecThs(-40),
    epsetCellUnderTempDetThs(-40),
    epsetCellUnderTempRecThs(-40),
    epsetCellDiscDetThs(5),
    epsetCellDiscDetTmo(0),
    epsetCellConnDetThs(5),
    epsetCellConnDetTmo(0),
    epsetExceptionRecTmo(0),
    epsetChgEventsDisable(0),
    epsetStateOfHealth(0x5555),
    epsetShBattNominalEnergy(9600),
    epsetShBattSerialModules(3),
    epsetEnMaxCurrentCtrl(0),
    epsetMasterCellVCheckDisable(0),
    epsetMasterCellTCheckDisable(0),
    epsetCellResistance(0),
    epsetExtModuleType(0),
    epsetEcsLowChSens(0),
    epsetEcsHighChSens(0),
    epsetContinuousBalEnable(0),
    epsetIcsSens(0)
{
    for(quint8 idx = 0; idx < 16; idx++){pMasterCellVolt->replace(idx, 0);}
    for(quint8 idx = 0; idx < 4; idx++){pMasterCellTemp->replace(idx, -32768);}
    for(quint8 idx = 0; idx < 3; idx++){pMasterBmsTemp->replace(idx, -32768);}
}

void DataProfile::updateLiveData(LiveData &liveData)
{
    QVector<qreal> cellVolt;
    QVector<qreal> cellTemp;
    QVector<qreal> bmsTemp;
    qreal minCellTemp;
    qreal maxCellTemp;
    qreal minBmsTemp;
    qreal maxBmsTemp;

    cellVolt.clear();
    for(quint8 idx = 0; idx < 16; idx++){cellVolt.append(liveData.masterCellVolt->at(idx) / 1000.0f);}

    cellTemp.clear();
    for(quint8 idx = 0; idx < 4; idx++)
    {
        if(-32768 != liveData.masterCellTemp->at(idx)){cellTemp.append(liveData.masterCellTemp->at(idx) / 10.0f);}
        else{cellTemp.append(liveData.masterCellTemp->at(idx));}
    }

    bmsTemp.clear();
    for(quint8 idx = 0; idx < 3; idx++)
    {
        if(-32768 != liveData.masterBmsTemp->at(idx)){bmsTemp.append(liveData.masterBmsTemp->at(idx) / 10.0f);}
        else{bmsTemp.append(liveData.masterBmsTemp->at(idx));}
    }

    if(-32768 != liveData.masterMinCellTemp){minCellTemp = liveData.masterMinCellTemp / 10.0f;}
    else{ minCellTemp = liveData.masterMinCellTemp;}

    if(-32768 != liveData.masterMaxCellTemp){maxCellTemp = liveData.masterMaxCellTemp / 10.0f;}
    else{maxCellTemp = liveData.masterMaxCellTemp;}

    if(-32768 != liveData.masterMinBmsTemp){minBmsTemp = liveData.masterMinBmsTemp / 10.0f;}
    else{minBmsTemp = liveData.masterMinBmsTemp;}

    if(-32768 != liveData.masterMaxBmsTemp){maxBmsTemp = liveData.masterMaxBmsTemp / 10.0f;}
    else{maxBmsTemp = liveData.masterMaxBmsTemp;}

    setMasterCellVolt(cellVolt);
    setMasterCellTemp(cellTemp);
    setMasterBmsTemp(bmsTemp);
    setMasterMinCellVoltage(liveData.masterMinCellVoltage / 1000.0f);
    setMasterMaxCellVoltage(liveData.masterMaxCellVoltage / 1000.0f);
    setMasterMinCellTemp(minCellTemp);
    setMasterMaxCellTemp(maxCellTemp);
    setMasterMinBmsTemp(minBmsTemp);
    setMasterMaxBmsTemp(maxBmsTemp);
    setMasterModuleVoltage(liveData.masterModuleVoltage / 1000.0f);
    setMasterBmsState(liveData.masterBmsState);
    setMasterBalancingBits(liveData.masterBalancingBits);
    setMasterBalancingDuration(liveData.masterBalancingDuration);
    setMasterLifeTimeCounter(liveData.masterLifeTimeCounter);
    setMasterPeriphStatus(liveData.masterPeriphStatus);

    if(-32768 != liveData.battMinCellTemp){minCellTemp = liveData.battMinCellTemp / 10.0f;}
    else{minCellTemp = liveData.battMinCellTemp;}

    if(-32768 != liveData.battMaxCellTemp){maxCellTemp = liveData.battMaxCellTemp / 10.0f;}
    else{maxCellTemp = liveData.battMaxCellTemp;}

    if(-32768 != liveData.battMinBmsTemp){minBmsTemp = liveData.battMinBmsTemp / 10.0f;}
    else{minBmsTemp = liveData.battMinBmsTemp;}

    if(-32768 != liveData.battMaxBmsTemp){maxBmsTemp = liveData.battMaxBmsTemp / 10.0f;}
    else{maxBmsTemp = liveData.battMaxBmsTemp;}

    setBattVoltage(liveData.battVoltage / 1000.0f);
    setBattMinCellVoltage(liveData.battMinCellVoltage / 1000.0f);
    setBattMaxCellVoltage(liveData.battMaxCellVoltage / 1000.0f);
    setBattMinCellTemp(minCellTemp);
    setBattMaxCellTemp(maxCellTemp);
    setBattMinBmsTemp(minBmsTemp);
    setBattMaxBmsTemp(maxBmsTemp);
    setBattIntCurrent(liveData.battIntCurrent / 10.0f);
    setBattIntCurrentAvg(liveData.battIntCurrentAvg / 10.0f);
    setBattExtCurrent(liveData.battExtCurrent / 10.0f);
    setBattExtCurrentAvg(liveData.battExtCurrentAvg / 10.0f);
    setBattCurrent(liveData.battCurrent / 10.0f);
    setBattCurrentAvg(liveData.battCurrentAvg / 10.0f);
    setBattStateOfCharge(liveData.battStateOfCharge / 1000000.0f);
    setBattStateOfHealth(liveData.battStateOfHealth / 100.0f);
    setBattAvailableEnergy(liveData.battAvailableEnergy / 1000.0f);
    setBattMaxChgCurrent(liveData.battMaxChgCurrent / 10.0f);
    setBattMaxDsgCurrent(liveData.battMaxDsgCurrent / 10.0f);
    setBattResVoltage(liveData.battResVoltage / 1000.0f);
    setBattSungrowStatus(liveData.battSungrowStatus);
    setBattExceptionL(liveData.battExceptionLStatus);
    setBattExceptionM(liveData.battExceptionMStatus);
}

void DataProfile::updateSettingsDataMaster(SettingsDataMaster &settingsDataMaster)
{
    setPsCellsInSeriesMod(settingsDataMaster.cellsInSeriesMod);
    setPsCellsInSeriesBatt(settingsDataMaster.cellsInSeriesBatt);
    setPsModulesInSeries(settingsDataMaster.modulesInSeries);
    setPsOverVoltageDetThreshold(settingsDataMaster.overVoltageDetThreshold * 10);
    setPsUnderVoltageDetThreshold(settingsDataMaster.underVoltageDetThreshold * 10);

    if(settingsDataMaster.modulesInSeries > 1)
    {
        setPsSlOverVoltageDetThreshold(settingsDataMaster.overVoltageDetThreshold * 10);
        setPsSlUnderVoltageDetThreshold(settingsDataMaster.underVoltageDetThreshold * 10);
    }
    else
    {
        setPsSlOverVoltageDetThreshold(4200);
        setPsSlUnderVoltageDetThreshold(2000);
    }

    setPsOperatingMode(settingsDataMaster.operatingMode);
    setPsMasterSlaveCommMode(settingsDataMaster.masterSlaveCommMode);
    setPsDpDsgSwitchType(settingsDataMaster.dpDsgSwitchType);
    setPsDpChgSwitchType(settingsDataMaster.dpChgSwitchType);
    setPsSpSwitchType(settingsDataMaster.spSwitchType);
    setPsSpSwitchMonitorType(settingsDataMaster.spSwitchMonitorType);
    setPsPreDsgSwitchType(settingsDataMaster.preDsgSwitchType);
    setPsPreDsgSwitchDuration(settingsDataMaster.preDsgSwitchDuration);
    setPsIgnitionType(settingsDataMaster.ignitionType);
    setPsChgDetectionType(settingsDataMaster.chgDetectionType);
    setPsChgIntDetectionHighThreshold(settingsDataMaster.chgIntDetectionHighThreshold);
    setPsChgIntDetectionLowThreshold(settingsDataMaster.chgIntDetectionLowThreshold);
    setPsDsgDetectionType(settingsDataMaster.dsgDetectionType);
    setPsDsgIntDetectionThreshold(settingsDataMaster.dsgIntDetectionThreshold);
    setPsChargerType(settingsDataMaster.chargerType);
    setPsEarlyBalancingThs(settingsDataMaster.earlyBalancingThreshold);
    setPsCellsAllowedDisbalance(settingsDataMaster.cellsAllowedDisbalance);
    setPsChgCompleteCurrent(settingsDataMaster.chgCompleteCurrent);
    setPsDsgCompleteCurrent(settingsDataMaster.dsgCompleteCurrent);
    setPsChgConnectionTmo(settingsDataMaster.chargerConnectionTmo);
    setPsDsgConnectionTmo(settingsDataMaster.loadConnectionTmo);
    setPsBatteryCapacity(settingsDataMaster.batteryCapacity);
    setPsStateOfCharge(settingsDataMaster.stateOfCharge);
    setPsFullyChgVoltageDetThs(settingsDataMaster.fullyChgVoltageDetThreshold);
    setPsFullyChgVoltageRecThs(settingsDataMaster.fullyChgVoltageRecThreshold);
    setPsFullyChgVoltageTolerance(settingsDataMaster.fullyChgVoltageTolerance);
    setPsFullyChgSwitchCtrlDisable(settingsDataMaster.fullyChgSwitchCtrlDisable);
    setPsAiInHighThreshold(settingsDataMaster.aiInHighThreshold);
    setPsAiInLowThreshold(settingsDataMaster.aiInLowThreshold);
    setPsExtOutputOCTmo(settingsDataMaster.extOutputOCTmo);
    setPsExtOutputOCRecTmo(settingsDataMaster.extOutputOCRecoveryTmo);
    setPsExtNtcSensorType(settingsDataMaster.extNtcSensorType);
    setPsExtNtcSensorEnStatus(settingsDataMaster.extNtcSensorEnStatus);
    setPsExtCurrentSensorType(settingsDataMaster.extCurrentSensorType);
    setPsExtCurrentSensorInvert(settingsDataMaster.extCurrentSensorInvert);
    setPsCurrentAvgLevel(settingsDataMaster.currentAvgLevel);
    setPsSwDiagnosticsDisable(settingsDataMaster.switchDiagnosticsDisable);
    setPseFullyDsgSwitchCtrlDisable(settingsDataMaster.fullyDsgSwitchCtrlDisable);
    setPseOverVoltageDetThs(settingsDataMaster.overVoltageDetThreshold);
    setPseOverVoltageRecThs(settingsDataMaster.overVoltageRecThreshold);
    setPseFullyDsgVoltageDetThs(settingsDataMaster.fullyDsgVoltageDetThreshold);
    setPseFullyDsgVoltageRecThs(settingsDataMaster.fullyDsgVoltageRecThreshold);
    setPseUnderVoltageDetThs(settingsDataMaster.underVoltageDetThreshold);
    setPseUnderVoltageRecThs(settingsDataMaster.underVoltageRecThreshold);
    setPseDsgOverCurrentDetThs1(settingsDataMaster.dsgOverCurrentDetThreshold_1);
    setPseDsgOverCurrentDetThs2(settingsDataMaster.dsgOverCurrentDetThreshold_2);
    setPseDsgOverCurrentDetTmo1(settingsDataMaster.dsgOverCurrentDetTmo_1);
    setPseDsgOverCurrentDetTmo2(settingsDataMaster.dsgOverCurrentDetTmo_2);
    setPseRegOverCurrentDetThs1(settingsDataMaster.regOverCurrentDetThreshold_1);
    setPseRegOverCurrentDetThs2(settingsDataMaster.regOverCurrentDetThreshold_2);
    setPseRegOverCurrentDetTmo1(settingsDataMaster.regOverCurrentDetTmo_1);
    setPseRegOverCurrentDetTmo2(settingsDataMaster.regOverCurrentDetTmo_2);
    setPseChgOverCurrentDetThs1(settingsDataMaster.chgOverCurrentDetThreshold_1);
    setPseChgOverCurrentDetThs2(settingsDataMaster.chgOverCurrentDetThreshold_2);
    setPseChgOverCurrentDetTmo1(settingsDataMaster.chgOverCurrentDetTmo_1);
    setPseChgOverCurrentDetTmo2(settingsDataMaster.chgOverCurrentDetTmo_2);
    setPseCellOverTempDetThs(settingsDataMaster.cellOverTempDetThreshold);
    setPseCellOverTempRecThs(settingsDataMaster.cellOverTempRecThreshold);
    setPseCellChgUnderTempDetThs(settingsDataMaster.cellChgUnderTempDetThreshold);
    setPseCellChgUnderTempRecThs(settingsDataMaster.cellChgUnderTempRecThreshold);
    setPseCellUnderTempDetThs(settingsDataMaster.cellUnderTempDetThreshold);
    setPseCellUnderTempRecThs(settingsDataMaster.cellUnderTempRecThreshold);
    setPseCellDiscDetThs(settingsDataMaster.cellDiscDetThreshold);
    setPseCellDiscDetTmo(settingsDataMaster.cellDiscDetTmo);
    setPseCellConnDetThs(settingsDataMaster.cellConnDetThreshold);
    setPseCellConnDetTmo(settingsDataMaster.cellConnDetTmo);
    setPseExceptionRecTmo(settingsDataMaster.exceptionRecoveryTmo);
    setPseChgEventsDisable(settingsDataMaster.chgEventsDisable);
    setPseStateOfHealth(settingsDataMaster.stateOfHealth);
    setPseShBattNominalEnergy(settingsDataMaster.sh10rtBattNominalEnergy);
    setPseShBattSerialModules(settingsDataMaster.sh10rtBattSerialModules);
    setPseEnMaxCurrentCtrl(settingsDataMaster.enMaxCurrentCtrl);
    setPseMasterCellVCheckDisable(settingsDataMaster.masterCellVoltCheckDisable);
    setPseMasterCellTCheckDisable(settingsDataMaster.masterCellTempCheckDisable);
    setPseCellResistance(settingsDataMaster.cellResistance);
    setPseExtModuleType(settingsDataMaster.extModuleType);
    setPseEcsLowChSens(settingsDataMaster.ecsLowChSensitivity);
    setPseEcsHighChSens(settingsDataMaster.ecsHighChSensitivity);
    setPseContinuousBalEnable(settingsDataMaster.continuousBalancingEnable);
    setPseIcsSens(settingsDataMaster.icsSensitivity);

    if(settingsDataMaster.dsgOverCurrentDetThreshold_2 > settingsDataMaster.dsgOverCurrentDetThreshold_1)
    {setPsDsgOcDetThreshold(settingsDataMaster.dsgOverCurrentDetThreshold_2);}
    else{setPsDsgOcDetThreshold(settingsDataMaster.dsgOverCurrentDetThreshold_1);}

    if(settingsDataMaster.chgOverCurrentDetThreshold_2 > settingsDataMaster.chgOverCurrentDetThreshold_1)
    {setPsChgOcDetThreshold(settingsDataMaster.chgOverCurrentDetThreshold_2);}
    else{setPsChgOcDetThreshold(settingsDataMaster.chgOverCurrentDetThreshold_1);}
}

// Live Data Master
QVector<qreal> DataProfile::getMasterCellVolt() const
{
    return *pMasterCellVolt;
}

void DataProfile::setMasterCellVolt(QVector<qreal> masterCellVolt)
{
    if (*pMasterCellVolt == masterCellVolt){ return; }

    *pMasterCellVolt = masterCellVolt;
    emit masterCellVoltChanged(*pMasterCellVolt);
}

QVector<qreal> DataProfile::getMasterCellTemp() const
{
    return *pMasterCellTemp;
}

void DataProfile::setMasterCellTemp(QVector<qreal> masterCellTemp)
{
    if (*pMasterCellTemp == masterCellTemp){ return; }

    *pMasterCellTemp = masterCellTemp;
    emit masterCellTempChanged(*pMasterCellTemp);
}

QVector<qreal> DataProfile::getMasterBmsTemp() const
{
    return *pMasterBmsTemp;
}

void DataProfile::setMasterBmsTemp(QVector<qreal> masterBmsTemp)
{
    if (*pMasterBmsTemp == masterBmsTemp){ return; }

    *pMasterBmsTemp = masterBmsTemp;
    emit masterBmsTempChanged(*pMasterBmsTemp);
}

qreal DataProfile::getMasterMinCellVoltage() const
{
    return pMasterMinCellVoltage;
}

void DataProfile::setMasterMinCellVoltage(qreal masterMinCellVoltage)
{
    if (qFuzzyCompare(pMasterMinCellVoltage, masterMinCellVoltage)){ return; }

    pMasterMinCellVoltage = masterMinCellVoltage;
    emit masterMinCellVoltageChanged(pMasterMinCellVoltage);
}

qreal DataProfile::getMasterMaxCellVoltage() const
{
    return pMasterMaxCellVoltage;
}

void DataProfile::setMasterMaxCellVoltage(qreal masterMaxCellVoltage)
{
    if (qFuzzyCompare(pMasterMaxCellVoltage, masterMaxCellVoltage)){ return; }

    pMasterMaxCellVoltage = masterMaxCellVoltage;
    emit masterMaxCellVoltageChanged(pMasterMaxCellVoltage);
}

qreal DataProfile::getMasterMinCellTemp() const
{
    return pMasterMinCellTemp;
}

void DataProfile::setMasterMinCellTemp(qreal masterMinCellTemp)
{
    if (qFuzzyCompare(pMasterMinCellTemp, masterMinCellTemp)){ return; }

    pMasterMinCellTemp = masterMinCellTemp;
    emit masterMinCellTempChanged(pMasterMinCellTemp);
}

qreal DataProfile::getMasterMaxCellTemp() const
{
    return pMasterMaxCellTemp;
}

void DataProfile::setMasterMaxCellTemp(qreal masterMaxCellTemp)
{
    if (qFuzzyCompare(pMasterMaxCellTemp, masterMaxCellTemp)){ return; }

    pMasterMaxCellTemp = masterMaxCellTemp;
    emit masterMaxCellTempChanged(pMasterMaxCellTemp);
}

qreal DataProfile::getMasterMinBmsTemp() const
{
    return pMasterMinBmsTemp;
}

void DataProfile::setMasterMinBmsTemp(qreal masterMinBmsTemp)
{
    if (qFuzzyCompare(pMasterMinBmsTemp, masterMinBmsTemp)){ return; }

    pMasterMinBmsTemp = masterMinBmsTemp;
    emit masterMinBmsTempChanged(pMasterMinBmsTemp);
}

qreal DataProfile::getMasterMaxBmsTemp() const
{
    return pMasterMaxBmsTemp;
}

void DataProfile::setMasterMaxBmsTemp(qreal masterMaxBmsTemp)
{
    if (qFuzzyCompare(pMasterMaxBmsTemp, masterMaxBmsTemp)){ return; }

    pMasterMaxBmsTemp = masterMaxBmsTemp;
    emit masterMaxBmsTempChanged(pMasterMaxBmsTemp);
}

qreal DataProfile::getMasterModuleVoltage() const
{
    return pMasterModuleVoltage;
}

void DataProfile::setMasterModuleVoltage(qreal masterModuleVoltage)
{
    if (qFuzzyCompare(pMasterModuleVoltage, masterModuleVoltage)){ return; }

    pMasterModuleVoltage = masterModuleVoltage;
    emit masterModuleVoltageChanged(pMasterModuleVoltage);
}

quint16 DataProfile::getMasterBmsState() const
{
    return pMasterBmsState;
}

void DataProfile::setMasterBmsState(quint16 masterBmsState)
{
    if (pMasterBmsState == masterBmsState){ return; }

    pMasterBmsState = masterBmsState;
    emit masterBmsStateChanged(pMasterBmsState);
}

quint16 DataProfile::getMasterBalancingBits() const
{
    return pMasterBalancingBits;
}

void DataProfile::setMasterBalancingBits(quint16 masterBalancingBits)
{
    if (pMasterBalancingBits == masterBalancingBits){ return; }

    pMasterBalancingBits = masterBalancingBits;
    emit masterBalancingBitsChanged(pMasterBalancingBits);
}

quint16 DataProfile::getMasterBalancingDuration() const
{
    return pMasterBalancingDuration;
}

void DataProfile::setMasterBalancingDuration(quint16 masterBalancingDuration)
{
    if (pMasterBalancingDuration == masterBalancingDuration){ return; }

    pMasterBalancingDuration = masterBalancingDuration;
    emit masterBalancingDurationChanged(pMasterBalancingDuration);
}

quint32 DataProfile::getMasterLifeTimeCounter() const
{
    return pMasterLifeTimeCounter;
}

void DataProfile::setMasterLifeTimeCounter(quint32 masterLifeTimeCounter)
{
    if (pMasterLifeTimeCounter == masterLifeTimeCounter){ return; }

    pMasterLifeTimeCounter = masterLifeTimeCounter;
    emit masterLifeTimeCounterChanged(pMasterLifeTimeCounter);
}

quint16 DataProfile::getMasterPeriphStatus() const
{
    return pMasterPeriphStatus;
}

void DataProfile::setMasterPeriphStatus(quint16 masterPeriphStatus)
{
    if (pMasterPeriphStatus == masterPeriphStatus){ return; }

    pMasterPeriphStatus = masterPeriphStatus;
    emit masterPeriphStatusChanged(pMasterPeriphStatus);
}

// Live Data Battery
qreal DataProfile::getBattVoltage() const
{
    return pBattVoltage;
}

void DataProfile::setBattVoltage(qreal battVoltage)
{
    if (qFuzzyCompare(pBattVoltage, battVoltage)){ return; }

    pBattVoltage = battVoltage;
    emit battVoltageChanged(pBattVoltage);
}

qreal DataProfile::getBattMinCellVoltage() const
{
    return pBattMinCellVoltage;
}

void DataProfile::setBattMinCellVoltage(qreal battMinCellVoltage)
{
    if (qFuzzyCompare(pBattMinCellVoltage, battMinCellVoltage)){ return; }

    pBattMinCellVoltage = battMinCellVoltage;
    emit battMinCellVoltageChanged(pBattMinCellVoltage);
}

qreal DataProfile::getBattMaxCellVoltage() const
{
    return pBattMaxCellVoltage;
}

void DataProfile::setBattMaxCellVoltage(qreal battMaxCellVoltage)
{
    if (qFuzzyCompare(pBattMaxCellVoltage, battMaxCellVoltage)){ return; }

    pBattMaxCellVoltage = battMaxCellVoltage;
    emit battMaxCellVoltageChanged(pBattMaxCellVoltage);
}

qreal DataProfile::getBattMinCellTemp() const
{
    return pBattMinCellTemp;
}

void DataProfile::setBattMinCellTemp(qreal battMinCellTemp)
{
    if (qFuzzyCompare(pBattMinCellTemp, battMinCellTemp)){ return; }

    pBattMinCellTemp = battMinCellTemp;
    emit battMinCellTempChanged(pBattMinCellTemp);
}

qreal DataProfile::getBattMaxCellTemp() const
{
    return pBattMaxCellTemp;
}

void DataProfile::setBattMaxCellTemp(qreal battMaxCellTemp)
{
    if (qFuzzyCompare(pBattMaxCellTemp, battMaxCellTemp)){ return; }

    pBattMaxCellTemp = battMaxCellTemp;
    emit battMaxCellTempChanged(pBattMaxCellTemp);
}

qreal DataProfile::getBattMinBmsTemp() const
{
    return pBattMinBmsTemp;
}

void DataProfile::setBattMinBmsTemp(qreal battMinBmsTemp)
{
    if (qFuzzyCompare(pBattMinBmsTemp, battMinBmsTemp)){ return; }

    pBattMinBmsTemp = battMinBmsTemp;
    emit battMinBmsTempChanged(pBattMinBmsTemp);
}

qreal DataProfile::getBattMaxBmsTemp() const
{
    return pBattMaxBmsTemp;
}

void DataProfile::setBattMaxBmsTemp(qreal battMaxBmsTemp)
{
    if (qFuzzyCompare(pBattMaxBmsTemp, battMaxBmsTemp)){ return; }

    pBattMaxBmsTemp = battMaxBmsTemp;
    emit battMaxBmsTempChanged(pBattMaxBmsTemp);
}

qreal DataProfile::getBattIntCurrent() const
{
    return pBattIntCurrent;
}

void DataProfile::setBattIntCurrent(qreal battIntCurrent)
{
    if (qFuzzyCompare(pBattIntCurrent, battIntCurrent)){ return; }

    pBattIntCurrent = battIntCurrent;
    emit battIntCurrentChanged(pBattIntCurrent);
}

qreal DataProfile::getBattIntCurrentAvg() const
{
    return pBattIntCurrentAvg;
}

void DataProfile::setBattIntCurrentAvg(qreal battIntCurrentAvg)
{
    if (qFuzzyCompare(pBattIntCurrentAvg, battIntCurrentAvg)){ return; }

    pBattIntCurrentAvg = battIntCurrentAvg;
    emit battIntCurrentAvgChanged(pBattIntCurrentAvg);
}

qreal DataProfile::getBattExtCurrent() const
{
    return pBattExtCurrent;
}

void DataProfile::setBattExtCurrent(qreal battExtCurrent)
{
    if (qFuzzyCompare(pBattExtCurrent, battExtCurrent)){ return; }

    pBattExtCurrent = battExtCurrent;
    emit battExtCurrentChanged(pBattExtCurrent);
}

qreal DataProfile::getBattExtCurrentAvg() const
{
    return pBattExtCurrentAvg;
}

void DataProfile::setBattExtCurrentAvg(qreal battExtCurrentAvg)
{
    if (qFuzzyCompare(pBattExtCurrentAvg, battExtCurrentAvg)){ return; }

    pBattExtCurrentAvg = battExtCurrentAvg;
    emit battExtCurrentAvgChanged(pBattExtCurrentAvg);
}

qreal DataProfile::getBattCurrent() const
{
    return pBattCurrent;
}

void DataProfile::setBattCurrent(qreal battCurrent)
{
    if (qFuzzyCompare(pBattCurrent, battCurrent)){ return; }

    pBattCurrent = battCurrent;
    emit battCurrentChanged(pBattCurrent);
}

qreal DataProfile::getBattCurrentAvg() const
{
    return pBattCurrentAvg;
}

void DataProfile::setBattCurrentAvg(qreal battCurrentAvg)
{
    if (qFuzzyCompare(pBattCurrentAvg, battCurrentAvg)){ return; }

    pBattCurrentAvg = battCurrentAvg;
    emit battCurrentAvgChanged(pBattCurrentAvg);
}

qreal DataProfile::getBattStateOfCharge() const
{
    return pBattStateOfCharge;
}

void DataProfile::setBattStateOfCharge(qreal battStateOfCharge)
{
    if (qFuzzyCompare(pBattStateOfCharge, battStateOfCharge)){ return; }

    pBattStateOfCharge = battStateOfCharge;
    emit battStateOfChargeChanged(pBattStateOfCharge);
}

qreal DataProfile::getBattStateOfHealth() const
{
    return pBattStateOfHealth;
}

void DataProfile::setBattStateOfHealth(qreal battStateOfHealth)
{
    if (qFuzzyCompare(pBattStateOfHealth,battStateOfHealth)){ return; }

    pBattStateOfHealth = battStateOfHealth;
    emit battStateOfHealthChanged(pBattStateOfHealth);
}

qreal DataProfile::getBattAvailableEnergy() const
{
    return pBattAvailableEnergy;
}

void DataProfile::setBattAvailableEnergy(qreal battAvailableEnergy)
{
    if (qFuzzyCompare(pBattAvailableEnergy, battAvailableEnergy)){ return; }

    pBattAvailableEnergy = battAvailableEnergy;
    emit battAvailableEnergyChanged(pBattAvailableEnergy);
}

qreal DataProfile::getBattMaxChgCurrent() const
{
    return pBattMaxChgCurrent;
}

void DataProfile::setBattMaxChgCurrent(qreal battMaxChgCurrent)
{
    if (qFuzzyCompare(pBattMaxChgCurrent, battMaxChgCurrent)){ return; }

    pBattMaxChgCurrent = battMaxChgCurrent;
    emit battMaxChgCurrentChanged(pBattMaxChgCurrent);
}

qreal DataProfile::getBattMaxDsgCurrent() const
{
    return pBattMaxDsgCurrent;
}

void DataProfile::setBattMaxDsgCurrent(qreal battMaxDsgCurrent)
{
    if (qFuzzyCompare(pBattMaxDsgCurrent, battMaxDsgCurrent)){ return; }

    pBattMaxDsgCurrent = battMaxDsgCurrent;
    emit battMaxDsgCurrentChanged(pBattMaxDsgCurrent);
}

qreal DataProfile::getBattResVoltage() const
{
    return pBattResVoltage;
}

void DataProfile::setBattResVoltage(qreal battResVoltage)
{
    if (qFuzzyCompare(pBattResVoltage, battResVoltage)){ return; }

    pBattResVoltage = battResVoltage;
    emit battResVoltageChanged(pBattResVoltage);
}

quint8 DataProfile::getBattSungrowStatus() const
{
    return pBattSungrowStatus;
}

void DataProfile::setBattSungrowStatus(quint8 battSungrowStatus)
{
    if (pBattSungrowStatus == battSungrowStatus){ return; }

    pBattSungrowStatus = battSungrowStatus;
    emit battSungrowStatusChanged(pBattSungrowStatus);
}

quint16 DataProfile::getBattExceptionL() const
{
    return pBattExceptionL;
}

void DataProfile::setBattExceptionL(quint16 battExceptionL)
{
    if (pBattExceptionL == battExceptionL){ return; }

    pBattExceptionL = battExceptionL;
    emit battExceptionLChanged(pBattExceptionL);
}

quint16 DataProfile::getBattExceptionM() const
{
    return pBattExceptionM;
}

void DataProfile::setBattExceptionM(quint16 battExceptionM)
{
    if (pBattExceptionM == battExceptionM){ return; }

    pBattExceptionM = battExceptionM;
    emit battExceptionMChanged(pBattExceptionM);
}

// Settings Master
quint8 DataProfile::getPsCellsInSeriesMod() const
{
    return psetCellsInSeriesMod;
}

void DataProfile::setPsCellsInSeriesMod(quint8 psCellsInSeriesMod)
{
    if (psetCellsInSeriesMod == psCellsInSeriesMod){ return; }

    psetCellsInSeriesMod = psCellsInSeriesMod;
    emit psCellsInSeriesModChanged(psetCellsInSeriesMod);
}

quint16 DataProfile::getPsCellsInSeriesBatt() const
{
    return psetCellsInSeriesBatt;
}

void DataProfile::setPsCellsInSeriesBatt(quint16 psCellsInSeriesBatt)
{
    if (psetCellsInSeriesBatt == psCellsInSeriesBatt){ return; }

    psetCellsInSeriesBatt = psCellsInSeriesBatt;
    emit psCellsInSeriesBattChanged(psetCellsInSeriesBatt);
}

quint8 DataProfile::getPsModulesInSeries() const
{
    return psetModulesInSeries;
}

void DataProfile::setPsModulesInSeries(quint8 psModulesInSeries)
{
    if (psetModulesInSeries == psModulesInSeries){ return; }

    psetModulesInSeries = psModulesInSeries;
    emit psModulesInSeriesChanged(psetModulesInSeries);
}

quint16 DataProfile::getPsOverVoltageDetThreshold() const
{
    return psetOverVoltageDetThreshold;
}

void DataProfile::setPsOverVoltageDetThreshold(quint16 psOverVoltageDetThreshold)
{
    if (psetOverVoltageDetThreshold == psOverVoltageDetThreshold){ return; }

    psetOverVoltageDetThreshold = psOverVoltageDetThreshold;
    emit psOverVoltageDetThresholdChanged(psetOverVoltageDetThreshold);
}

quint16 DataProfile::getPsUnderVoltageDetThreshold() const
{
    return psetUnderVoltageDetThreshold;
}

void DataProfile::setPsUnderVoltageDetThreshold(quint16 psUnderVoltageDetThreshold)
{
    if (psetUnderVoltageDetThreshold == psUnderVoltageDetThreshold){ return; }

    psetUnderVoltageDetThreshold = psUnderVoltageDetThreshold;
    emit psUnderVoltageDetThresholdChanged(psetUnderVoltageDetThreshold);
}

quint16 DataProfile::getPsSlOverVoltageDetThreshold() const
{
    return psetSlOverVoltageDetThreshold;
}

void DataProfile::setPsSlOverVoltageDetThreshold(quint16 psSlOverVoltageDetThreshold)
{
    if (psetSlOverVoltageDetThreshold == psSlOverVoltageDetThreshold){ return; }

    psetSlOverVoltageDetThreshold = psSlOverVoltageDetThreshold;
    emit psSlOverVoltageDetThresholdChanged(psetSlOverVoltageDetThreshold);
}

quint16 DataProfile::getPsSlUnderVoltageDetThreshold() const
{
    return psetSlUnderVoltageDetThreshold;
}

void DataProfile::setPsSlUnderVoltageDetThreshold(quint16 psSlUnderVoltageDetThreshold)
{
    if (psetSlUnderVoltageDetThreshold == psSlUnderVoltageDetThreshold){ return; }

    psetSlUnderVoltageDetThreshold = psSlUnderVoltageDetThreshold;
    emit psSlUnderVoltageDetThresholdChanged(psetSlUnderVoltageDetThreshold);
}

quint16 DataProfile::getPsDsgOcDetThreshold() const
{
    return psetDsgOcDetThreshold;
}

void DataProfile::setPsDsgOcDetThreshold(quint16 psDsgOcDetThreshold)
{
    if (psetDsgOcDetThreshold == psDsgOcDetThreshold){ return; }

    psetDsgOcDetThreshold = psDsgOcDetThreshold;
    emit psDsgOcDetThresholdChanged(psetDsgOcDetThreshold);
}

quint16 DataProfile::getPsChgOcDetThreshold() const
{
    return psetChgOcDetThreshold;
}

void DataProfile::setPsChgOcDetThreshold(quint16 psChgOcDetThreshold)
{
    if (psetChgOcDetThreshold == psChgOcDetThreshold){ return; }

    psetChgOcDetThreshold = psChgOcDetThreshold;
    emit psChgOcDetThresholdChanged(psetChgOcDetThreshold);
}

quint8 DataProfile::getPsOperatingMode() const
{
    return psetOperatingMode;
}

void DataProfile::setPsOperatingMode(quint8 psOperatingMode)
{
    if (psetOperatingMode == psOperatingMode){ return; }

    psetOperatingMode = psOperatingMode;
    emit psOperatingModeChanged(psetOperatingMode);
}

quint8 DataProfile::getPsMasterSlaveCommMode() const
{
    return psetMasterSlaveCommMode;
}

void DataProfile::setPsMasterSlaveCommMode(quint8 psMasterSlaveCommMode)
{
    if (psetMasterSlaveCommMode == psMasterSlaveCommMode){ return; }

    psetMasterSlaveCommMode = psMasterSlaveCommMode;
    emit psMasterSlaveCommModeChanged(psetMasterSlaveCommMode);
}

quint8 DataProfile::getPsDpDsgSwitchType() const
{
    return psetDpDsgSwitchType;
}

void DataProfile::setPsDpDsgSwitchType(quint8 psDpDsgSwitchType)
{
    if (psetDpDsgSwitchType == psDpDsgSwitchType){ return; }

    psetDpDsgSwitchType = psDpDsgSwitchType;
    emit psDpDsgSwitchTypeChanged(psetDpDsgSwitchType);
}

quint8 DataProfile::getPsDpChgSwitchType() const
{
    return psetDpChgSwitchType;
}

void DataProfile::setPsDpChgSwitchType(quint8 psDpChgSwitchType)
{
    if (psetDpChgSwitchType == psDpChgSwitchType){ return; }

    psetDpChgSwitchType = psDpChgSwitchType;
    emit psDpChgSwitchTypeChanged(psetDpChgSwitchType);
}

quint8 DataProfile::getPsSpSwitchType() const
{
    return psetSpSwitchType;
}

void DataProfile::setPsSpSwitchType(quint8 psSpSwitchType)
{
    if (psetSpSwitchType == psSpSwitchType){ return; }

    psetSpSwitchType = psSpSwitchType;
    emit psSpSwitchTypeChanged(psetSpSwitchType);
}

quint8 DataProfile::getPsSpSwitchMonitorType() const
{
    return psetSpSwitchMonitorType;
}

void DataProfile::setPsSpSwitchMonitorType(quint8 psSpSwitchMonitorType)
{
    if (psetSpSwitchMonitorType == psSpSwitchMonitorType){ return; }

    psetSpSwitchMonitorType = psSpSwitchMonitorType;
    emit psSpSwitchMonitorTypeChanged(psetSpSwitchMonitorType);
}

quint8 DataProfile::getPsPreDsgSwitchType() const
{
    return psetPreDsgSwitchType;
}

void DataProfile::setPsPreDsgSwitchType(quint8 psPreDsgSwitchType)
{
    if (psetPreDsgSwitchType == psPreDsgSwitchType){ return; }

    psetPreDsgSwitchType = psPreDsgSwitchType;
    emit psPreDsgSwitchTypeChanged(psetPreDsgSwitchType);
}

quint8 DataProfile::getPsPreDsgSwitchDuration() const
{
    return psetPreDsgSwitchDuration;
}

void DataProfile::setPsPreDsgSwitchDuration(quint8 psPreDsgSwitchDuration)
{
    if (psetPreDsgSwitchDuration == psPreDsgSwitchDuration){ return; }

    psetPreDsgSwitchDuration = psPreDsgSwitchDuration;
    emit psPreDsgSwitchDurationChanged(psetPreDsgSwitchDuration);
}

quint8 DataProfile::getPsIgnitionType() const
{
    return psetIgnitionType;
}

void DataProfile::setPsIgnitionType(quint8 psIgnitionType)
{
    if (psetIgnitionType == psIgnitionType){ return; }

    psetIgnitionType = psIgnitionType;
    emit psIgnitionTypeChanged(psetIgnitionType);
}

quint8 DataProfile::getPsChgDetectionType() const
{
    return psetChgDetectionType;
}

void DataProfile::setPsChgDetectionType(quint8 psChgDetectionType)
{
    if (psetChgDetectionType == psChgDetectionType){ return; }

    psetChgDetectionType = psChgDetectionType;
    emit psChgDetectionTypeChanged(psetChgDetectionType);
}

quint8 DataProfile::getPsChgIntDetectionHighThreshold() const
{
    return psetChgIntDetectionHighThreshold;
}

void DataProfile::setPsChgIntDetectionHighThreshold(quint8 psChgIntDetectionHighThreshold)
{
    if (psetChgIntDetectionHighThreshold == psChgIntDetectionHighThreshold){ return; }

    psetChgIntDetectionHighThreshold = psChgIntDetectionHighThreshold;
    emit psChgIntDetectionHighThresholdChanged(psetChgIntDetectionHighThreshold);
}

quint8 DataProfile::getPsChgIntDetectionLowThreshold() const
{
    return psetChgIntDetectionLowThreshold;
}

void DataProfile::setPsChgIntDetectionLowThreshold(quint8 psChgIntDetectionLowThreshold)
{
    if (psetChgIntDetectionLowThreshold == psChgIntDetectionLowThreshold){ return; }

    psetChgIntDetectionLowThreshold = psChgIntDetectionLowThreshold;
    emit psChgIntDetectionLowThresholdChanged(psetChgIntDetectionLowThreshold);
}

quint8 DataProfile::getPsDsgDetectionType() const
{
    return psetDsgDetectionType;
}

void DataProfile::setPsDsgDetectionType(quint8 psDsgDetectionType)
{
    if (psetDsgDetectionType == psDsgDetectionType){ return; }

    psetDsgDetectionType = psDsgDetectionType;
    emit psDsgDetectionTypeChanged(psetDsgDetectionType);
}

quint8 DataProfile::getPsDsgIntDetectionThreshold() const
{
    return psetDsgIntDetectionThreshold;
}

void DataProfile::setPsDsgIntDetectionThreshold(quint8 psDsgIntDetectionThreshold)
{
    if (psetDsgIntDetectionThreshold == psDsgIntDetectionThreshold){ return; }

    psetDsgIntDetectionThreshold = psDsgIntDetectionThreshold;
    emit psDsgIntDetectionThresholdChanged(psetDsgIntDetectionThreshold);
}

quint8 DataProfile::getPsChargerType() const
{
    return psetChargerType;
}

void DataProfile::setPsChargerType(quint8 psChargerType)
{
    if (psetChargerType == psChargerType){ return; }

    psetChargerType = psChargerType;
    emit psChargerTypeChanged(psetChargerType);
}

quint16 DataProfile::getPsEarlyBalancingThs() const
{
    return psetEarlyBalancingThs;
}

void DataProfile::setPsEarlyBalancingThs(quint16 psEarlyBalancingThs)
{
    if (psetEarlyBalancingThs == psEarlyBalancingThs){ return; }

    psetEarlyBalancingThs = psEarlyBalancingThs;
    emit psEarlyBalancingThsChanged(psetEarlyBalancingThs);
}

quint16 DataProfile::getPsCellsAllowedDisbalance() const
{
    return psetCellsAllowedDisbalance;
}

void DataProfile::setPsCellsAllowedDisbalance(quint16 psCellsAllowedDisbalance)
{
    if (psetCellsAllowedDisbalance == psCellsAllowedDisbalance){ return; }

    psetCellsAllowedDisbalance = psCellsAllowedDisbalance;
    emit psCellsAllowedDisbalanceChanged(psetCellsAllowedDisbalance);
}

quint16 DataProfile::getPsChgCompleteCurrent() const
{
    return psetChgCompleteCurrent;
}

void DataProfile::setPsChgCompleteCurrent(quint16 psChgCompleteCurrent)
{
    if (psetChgCompleteCurrent == psChgCompleteCurrent){ return; }

    psetChgCompleteCurrent = psChgCompleteCurrent;
    emit psChgCompleteCurrentChanged(psetChgCompleteCurrent);
}

quint16 DataProfile::getPsDsgCompleteCurrent() const
{
    return psetDsgCompleteCurrent;
}

void DataProfile::setPsDsgCompleteCurrent(quint16 psDsgCompleteCurrent)
{
    if (psetDsgCompleteCurrent == psDsgCompleteCurrent){ return; }

    psetDsgCompleteCurrent = psDsgCompleteCurrent;
    emit psDsgCompleteCurrentChanged(psetDsgCompleteCurrent);
}

quint8 DataProfile::getPsChgConnectionTmo() const
{
    return psetChgConnectionTmo;
}

void DataProfile::setPsChgConnectionTmo(quint8 psChgConnectionTmo)
{
    if (psetChgConnectionTmo == psChgConnectionTmo){ return; }

    psetChgConnectionTmo = psChgConnectionTmo;
    emit psChgConnectionTmoChanged(psetChgConnectionTmo);
}

quint8 DataProfile::getPsDsgConnectionTmo() const
{
    return psetDsgConnectionTmo;
}

void DataProfile::setPsDsgConnectionTmo(quint8 psDsgConnectionTmo)
{
    if (psetDsgConnectionTmo == psDsgConnectionTmo){ return; }

    psetDsgConnectionTmo = psDsgConnectionTmo;
    emit psDsgConnectionTmoChanged(psetDsgConnectionTmo);
}

quint32 DataProfile::getPsBatteryCapacity() const
{
    return psetBatteryCapacity;
}

void DataProfile::setPsBatteryCapacity(quint32 psBatteryCapacity)
{
    if (psetBatteryCapacity == psBatteryCapacity){ return; }

    psetBatteryCapacity = psBatteryCapacity;
    emit psBatteryCapacityChanged(psetBatteryCapacity);
}

quint16 DataProfile::getPsStateOfCharge() const
{
    return psetStateOfCharge;
}

void DataProfile::setPsStateOfCharge(quint16 psStateOfCharge)
{
    if (psetStateOfCharge == psStateOfCharge){ return; }

    psetStateOfCharge = psStateOfCharge;
    emit psStateOfChargeChanged(psetStateOfCharge);
}

quint16 DataProfile::getPsFullyChgVoltageDetThs() const
{
    return psetFullyChgVoltageDetThs;
}

void DataProfile::setPsFullyChgVoltageDetThs(quint16 psFullyChgVoltageDetThs)
{
    if (psetFullyChgVoltageDetThs == psFullyChgVoltageDetThs){ return; }

    psetFullyChgVoltageDetThs = psFullyChgVoltageDetThs;
    emit psFullyChgVoltageDetThsChanged(psetFullyChgVoltageDetThs);
}

quint16 DataProfile::getPsFullyChgVoltageRecThs() const
{
    return psetFullyChgVoltageRecThs;
}

void DataProfile::setPsFullyChgVoltageRecThs(quint16 psFullyChgVoltageRecThs)
{
    if (psetFullyChgVoltageRecThs == psFullyChgVoltageRecThs){ return; }

    psetFullyChgVoltageRecThs = psFullyChgVoltageRecThs;
    emit psFullyChgVoltageRecThsChanged(psetFullyChgVoltageRecThs);
}

quint16 DataProfile::getPsFullyChgVoltageTolerance() const
{
    return psetFullyChgVoltageTolerance;
}

void DataProfile::setPsFullyChgVoltageTolerance(quint16 psFullyChgVoltageTolerance)
{
    if (psetFullyChgVoltageTolerance == psFullyChgVoltageTolerance){ return; }

    psetFullyChgVoltageTolerance = psFullyChgVoltageTolerance;
    emit psFullyChgVoltageToleranceChanged(psetFullyChgVoltageTolerance);
}

quint8 DataProfile::getPsFullyChgSwitchCtrlDisable() const
{
    return psetFullyChgSwitchCtrlDisable;
}

void DataProfile::setPsFullyChgSwitchCtrlDisable(quint8 psFullyChgSwitchCtrlDisable)
{
    if (psetFullyChgSwitchCtrlDisable == psFullyChgSwitchCtrlDisable){ return; }

    psetFullyChgSwitchCtrlDisable = psFullyChgSwitchCtrlDisable;
    emit psFullyChgSwitchCtrlDisableChanged(psetFullyChgSwitchCtrlDisable);
}

quint16 DataProfile::getPsAiInHighThreshold() const
{
    return psetAiInHighThreshold;
}

void DataProfile::setPsAiInHighThreshold(quint16 psAiInHighThreshold)
{
    if (psetAiInHighThreshold == psAiInHighThreshold){ return; }

    psetAiInHighThreshold = psAiInHighThreshold;
    emit psAiInHighThresholdChanged(psetAiInHighThreshold);
}

quint16 DataProfile::getPsAiInLowThreshold() const
{
    return psetAiInLowThreshold;
}

void DataProfile::setPsAiInLowThreshold(quint16 psAiInLowThreshold)
{
    if (psetAiInLowThreshold == psAiInLowThreshold){ return; }

    psetAiInLowThreshold = psAiInLowThreshold;
    emit psAiInLowThresholdChanged(psetAiInLowThreshold);
}

quint16 DataProfile::getPsExtOutputOCTmo() const
{
    return psetExtOutputOCTmo;
}

void DataProfile::setPsExtOutputOCTmo(quint16 psExtOutputOCTmo)
{
    if (psetExtOutputOCTmo == psExtOutputOCTmo){ return; }

    psetExtOutputOCTmo = psExtOutputOCTmo;
    emit psExtOutputOCTmoChanged(psetExtOutputOCTmo);
}

quint16 DataProfile::getPsExtOutputOCRecTmo() const
{
    return psetExtOutputOCRecTmo;
}

void DataProfile::setPsExtOutputOCRecTmo(quint16 psExtOutputOCRecTmo)
{
    if (psetExtOutputOCRecTmo == psExtOutputOCRecTmo){ return; }

    psetExtOutputOCRecTmo = psExtOutputOCRecTmo;
    emit psExtOutputOCRecTmoChanged(psetExtOutputOCRecTmo);
}

quint8 DataProfile::getPsExtNtcSensorType() const
{
    return psetExtNtcSensorType;
}

void DataProfile::setPsExtNtcSensorType(quint8 psExtNtcSensorType)
{
    if (psetExtNtcSensorType == psExtNtcSensorType){ return; }

    psetExtNtcSensorType = psExtNtcSensorType;
    emit psExtNtcSensorTypeChanged(psetExtNtcSensorType);
}

quint8 DataProfile::getPsExtNtcSensorEnStatus() const
{
    return psetExtNtcSensorEnStatus;
}

void DataProfile::setPsExtNtcSensorEnStatus(quint8 psExtNtcSensorEnStatus)
{
    if (psetExtNtcSensorEnStatus == psExtNtcSensorEnStatus){ return; }

    psetExtNtcSensorEnStatus = psExtNtcSensorEnStatus;
    emit psExtNtcSensorEnStatusChanged(psetExtNtcSensorEnStatus);
}

quint8 DataProfile::getPsExtCurrentSensorType() const
{
    return psetExtCurrentSensorType;
}

void DataProfile::setPsExtCurrentSensorType(quint8 psExtCurrentSensorType)
{
    if (psetExtCurrentSensorType == psExtCurrentSensorType){ return; }

    psetExtCurrentSensorType = psExtCurrentSensorType;
    emit psExtCurrentSensorTypeChanged(psetExtCurrentSensorType);
}

quint8 DataProfile::getPsExtCurrentSensorInvert() const
{
    return psetExtCurrentSensorInvert;
}

void DataProfile::setPsExtCurrentSensorInvert(quint8 psExtCurrentSensorInvert)
{
    if (psetExtCurrentSensorInvert == psExtCurrentSensorInvert){ return; }

    psetExtCurrentSensorInvert = psExtCurrentSensorInvert;
    emit psExtCurrentSensorInvertChanged(psetExtCurrentSensorInvert);
}

quint8 DataProfile::getPsCurrentAvgLevel() const
{
    return psetCurrentAvgLevel;
}

void DataProfile::setPsCurrentAvgLevel(quint8 psCurrentAvgLevel)
{
    if (psetCurrentAvgLevel == psCurrentAvgLevel){ return; }

    psetCurrentAvgLevel = psCurrentAvgLevel;
    emit psCurrentAvgLevelChanged(psetCurrentAvgLevel);
}

quint8 DataProfile::getPsSwDiagnosticsDisable() const
{
    return psetSwDiagnosticsDisable;
}

void DataProfile::setPsSwDiagnosticsDisable(quint8 psSwDiagnosticsDisable)
{
    if (psetSwDiagnosticsDisable == psSwDiagnosticsDisable){ return; }

    psetSwDiagnosticsDisable = psSwDiagnosticsDisable;
    emit psSwDiagnosticsDisableChanged(psetSwDiagnosticsDisable);
}

quint8 DataProfile::getPseFullyDsgSwitchCtrlDisable() const
{
    return epsetFullyDsgSwitchCtrlDisable;
}

void DataProfile::setPseFullyDsgSwitchCtrlDisable(quint8 pseFullyDsgSwitchCtrlDisable)
{
    if (epsetFullyDsgSwitchCtrlDisable == pseFullyDsgSwitchCtrlDisable){ return; }

    epsetFullyDsgSwitchCtrlDisable = pseFullyDsgSwitchCtrlDisable;
    emit pseFullyDsgSwitchCtrlDisableChanged(epsetFullyDsgSwitchCtrlDisable);
}

quint16 DataProfile::getPseOverVoltageDetThs() const
{
    return epsetOverVoltageDetThs;
}

void DataProfile::setPseOverVoltageDetThs(quint16 pseOverVoltageDetThs)
{
    if (epsetOverVoltageDetThs == pseOverVoltageDetThs){ return; }

    epsetOverVoltageDetThs = pseOverVoltageDetThs;
    emit pseOverVoltageDetThsChanged(epsetOverVoltageDetThs);
}

quint16 DataProfile::getPseOverVoltageRecThs() const
{
    return epsetOverVoltageRecThs;
}

void DataProfile::setPseOverVoltageRecThs(quint16 pseOverVoltageRecThs)
{
    if (epsetOverVoltageRecThs == pseOverVoltageRecThs){ return; }

    epsetOverVoltageRecThs = pseOverVoltageRecThs;
    emit pseOverVoltageRecThsChanged(epsetOverVoltageRecThs);
}

quint16 DataProfile::getPseFullyDsgVoltageDetThs() const
{
    return epsetFullyDsgVoltageDetThs;
}

void DataProfile::setPseFullyDsgVoltageDetThs(quint16 pseFullyDsgVoltageDetThs)
{
    if (epsetFullyDsgVoltageDetThs == pseFullyDsgVoltageDetThs){ return; }

    epsetFullyDsgVoltageDetThs = pseFullyDsgVoltageDetThs;
    emit pseFullyDsgVoltageDetThsChanged(epsetFullyDsgVoltageDetThs);
}

quint16 DataProfile::getPseFullyDsgVoltageRecThs() const
{
    return epsetFullyDsgVoltageRecThs;
}

void DataProfile::setPseFullyDsgVoltageRecThs(quint16 pseFullyDsgVoltageRecThs)
{
    if (epsetFullyDsgVoltageRecThs == pseFullyDsgVoltageRecThs){ return; }

    epsetFullyDsgVoltageRecThs = pseFullyDsgVoltageRecThs;
    emit pseFullyDsgVoltageRecThsChanged(epsetFullyDsgVoltageRecThs);
}

quint16 DataProfile::getPseUnderVoltageDetThs() const
{
    return epsetUnderVoltageDetThs;
}

void DataProfile::setPseUnderVoltageDetThs(quint16 pseUnderVoltageDetThs)
{
    if (epsetUnderVoltageDetThs == pseUnderVoltageDetThs){ return; }

    epsetUnderVoltageDetThs = pseUnderVoltageDetThs;
    emit pseUnderVoltageDetThsChanged(epsetUnderVoltageDetThs);
}

quint16 DataProfile::getPseUnderVoltageRecThs() const
{
    return epsetUnderVoltageRecThs;
}

void DataProfile::setPseUnderVoltageRecThs(quint16 pseUnderVoltageRecThs)
{
    if (epsetUnderVoltageRecThs == pseUnderVoltageRecThs){ return; }

    epsetUnderVoltageRecThs = pseUnderVoltageRecThs;
    emit pseUnderVoltageRecThsChanged(epsetUnderVoltageRecThs);
}

quint16 DataProfile::getPseDsgOverCurrentDetThs1() const
{
    return epsetDsgOverCurrentDetThs1;
}


void DataProfile::setPseDsgOverCurrentDetThs1(quint16 pseDsgOverCurrentDetThs1)
{
    if (epsetDsgOverCurrentDetThs1 == pseDsgOverCurrentDetThs1){ return; }

    epsetDsgOverCurrentDetThs1 = pseDsgOverCurrentDetThs1;
    emit pseDsgOverCurrentDetThs1Changed(epsetDsgOverCurrentDetThs1);
}

quint16 DataProfile::getPseDsgOverCurrentDetThs2() const
{
    return epsetDsgOverCurrentDetThs2;
}

void DataProfile::setPseDsgOverCurrentDetThs2(quint16 pseDsgOverCurrentDetThs2)
{
    if (epsetDsgOverCurrentDetThs2 == pseDsgOverCurrentDetThs2){ return; }

    epsetDsgOverCurrentDetThs2 = pseDsgOverCurrentDetThs2;
    emit pseDsgOverCurrentDetThs2Changed(epsetDsgOverCurrentDetThs2);
}

quint16 DataProfile::getPseDsgOverCurrentDetTmo1() const
{
    return epsetDsgOverCurrentDetTmo1;
}

void DataProfile::setPseDsgOverCurrentDetTmo1(quint16 pseDsgOverCurrentDetTmo1)
{
    if (epsetDsgOverCurrentDetTmo1 == pseDsgOverCurrentDetTmo1){ return; }

    epsetDsgOverCurrentDetTmo1 = pseDsgOverCurrentDetTmo1;
    emit pseDsgOverCurrentDetTmo1Changed(epsetDsgOverCurrentDetTmo1);
}

quint16 DataProfile::getPseDsgOverCurrentDetTmo2() const
{
    return epsetDsgOverCurrentDetTmo2;
}

void DataProfile::setPseDsgOverCurrentDetTmo2(quint16 pseDsgOverCurrentDetTmo2)
{
    if (epsetDsgOverCurrentDetTmo2 == pseDsgOverCurrentDetTmo2){ return; }

    epsetDsgOverCurrentDetTmo2 = pseDsgOverCurrentDetTmo2;
    emit pseDsgOverCurrentDetTmo2Changed(epsetDsgOverCurrentDetTmo2);
}

quint16 DataProfile::getPseRegOverCurrentDetThs1() const
{
    return epsetRegOverCurrentDetThs1;
}

void DataProfile::setPseRegOverCurrentDetThs1(quint16 pseRegOverCurrentDetThs1)
{
    if (epsetRegOverCurrentDetThs1 == pseRegOverCurrentDetThs1){ return; }

    epsetRegOverCurrentDetThs1 = pseRegOverCurrentDetThs1;
    emit pseRegOverCurrentDetThs1Changed(epsetRegOverCurrentDetThs1);
}

quint16 DataProfile::getPseRegOverCurrentDetThs2() const
{
    return epsetRegOverCurrentDetThs2;
}

void DataProfile::setPseRegOverCurrentDetThs2(quint16 pseRegOverCurrentDetThs2)
{
    if (epsetRegOverCurrentDetThs2 == pseRegOverCurrentDetThs2){ return; }

    epsetRegOverCurrentDetThs2 = pseRegOverCurrentDetThs2;
    emit pseRegOverCurrentDetThs2Changed(epsetRegOverCurrentDetThs2);
}

quint16 DataProfile::getPseRegOverCurrentDetTmo1() const
{
    return epsetRegOverCurrentDetTmo1;
}

void DataProfile::setPseRegOverCurrentDetTmo1(quint16 pseRegOverCurrentDetTmo1)
{
    if (epsetRegOverCurrentDetTmo1 == pseRegOverCurrentDetTmo1){ return; }

    epsetRegOverCurrentDetTmo1 = pseRegOverCurrentDetTmo1;
    emit pseRegOverCurrentDetTmo1Changed(epsetRegOverCurrentDetTmo1);
}

quint16 DataProfile::getPseRegOverCurrentDetTmo2() const
{
    return epsetRegOverCurrentDetTmo2;
}

void DataProfile::setPseRegOverCurrentDetTmo2(quint16 pseRegOverCurrentDetTmo2)
{
    if (epsetRegOverCurrentDetTmo2 == pseRegOverCurrentDetTmo2){ return; }

    epsetRegOverCurrentDetTmo2 = pseRegOverCurrentDetTmo2;
    emit pseRegOverCurrentDetTmo2Changed(epsetRegOverCurrentDetTmo2);
}

quint16 DataProfile::getPseChgOverCurrentDetThs1() const
{
    return epsetChgOverCurrentDetThs1;
}

void DataProfile::setPseChgOverCurrentDetThs1(quint16 pseChgOverCurrentDetThs1)
{
    if (epsetChgOverCurrentDetThs1 == pseChgOverCurrentDetThs1){ return; }

    epsetChgOverCurrentDetThs1 = pseChgOverCurrentDetThs1;
    emit pseChgOverCurrentDetThs1Changed(epsetChgOverCurrentDetThs1);
}

quint16 DataProfile::getPseChgOverCurrentDetThs2() const
{
    return epsetChgOverCurrentDetThs2;
}

void DataProfile::setPseChgOverCurrentDetThs2(quint16 pseChgOverCurrentDetThs2)
{
    if (epsetChgOverCurrentDetThs2 == pseChgOverCurrentDetThs2){ return; }

    epsetChgOverCurrentDetThs2 = pseChgOverCurrentDetThs2;
    emit pseChgOverCurrentDetThs2Changed(epsetChgOverCurrentDetThs2);
}

quint16 DataProfile::getPseChgOverCurrentDetTmo1() const
{
    return epsetChgOverCurrentDetTmo1;
}

void DataProfile::setPseChgOverCurrentDetTmo1(quint16 pseChgOverCurrentDetTmo1)
{
    if (epsetChgOverCurrentDetTmo1 == pseChgOverCurrentDetTmo1){ return; }

    epsetChgOverCurrentDetTmo1 = pseChgOverCurrentDetTmo1;
    emit pseChgOverCurrentDetTmo1Changed(epsetChgOverCurrentDetTmo1);
}

quint16 DataProfile::getPseChgOverCurrentDetTmo2() const
{
    return epsetChgOverCurrentDetTmo2;
}

void DataProfile::setPseChgOverCurrentDetTmo2(quint16 pseChgOverCurrentDetTmo2)
{
    if (epsetChgOverCurrentDetTmo2 == pseChgOverCurrentDetTmo2){ return; }

    epsetChgOverCurrentDetTmo2 = pseChgOverCurrentDetTmo2;
    emit pseChgOverCurrentDetTmo2Changed(epsetChgOverCurrentDetTmo2);
}

qint16 DataProfile::getPseCellOverTempDetThs() const
{
    return epsetCellOverTempDetThs;
}

void DataProfile::setPseCellOverTempDetThs(qint16 pseCellOverTempDetThs)
{
    if (epsetCellOverTempDetThs == pseCellOverTempDetThs){ return; }

    epsetCellOverTempDetThs = pseCellOverTempDetThs;
    emit pseCellOverTempDetThsChanged(epsetCellOverTempDetThs);
}

qint16 DataProfile::getPseCellOverTempRecThs() const
{
    return epsetCellOverTempRecThs;
}

void DataProfile::setPseCellOverTempRecThs(qint16 pseCellOverTempRecThs)
{
    if (epsetCellOverTempRecThs == pseCellOverTempRecThs){ return; }

    epsetCellOverTempRecThs = pseCellOverTempRecThs;
    emit pseCellOverTempRecThsChanged(epsetCellOverTempRecThs);
}

qint16 DataProfile::getPseCellChgUnderTempDetThs() const
{
    return epsetCellChgUnderTempDetThs;
}

void DataProfile::setPseCellChgUnderTempDetThs(qint16 pseCellChgUnderTempDetThs)
{
    if (epsetCellChgUnderTempDetThs == pseCellChgUnderTempDetThs){ return; }

    epsetCellChgUnderTempDetThs = pseCellChgUnderTempDetThs;
    emit pseCellChgUnderTempDetThsChanged(epsetCellChgUnderTempDetThs);
}

qint16 DataProfile::getPseCellChgUnderTempRecThs() const
{
    return epsetCellChgUnderTempRecThs;
}

void DataProfile::setPseCellChgUnderTempRecThs(qint16 pseCellChgUnderTempRecThs)
{
    if (epsetCellChgUnderTempRecThs == pseCellChgUnderTempRecThs){ return; }

    epsetCellChgUnderTempRecThs = pseCellChgUnderTempRecThs;
    emit pseCellChgUnderTempRecThsChanged(epsetCellChgUnderTempRecThs);
}

qint16 DataProfile::getPseCellUnderTempDetThs() const
{
    return epsetCellUnderTempDetThs;
}

void DataProfile::setPseCellUnderTempDetThs(qint16 pseCellUnderTempDetThs)
{
    if (epsetCellUnderTempDetThs == pseCellUnderTempDetThs){ return; }

    epsetCellUnderTempDetThs = pseCellUnderTempDetThs;
    emit pseCellUnderTempDetThsChanged(epsetCellUnderTempDetThs);
}

qint16 DataProfile::getPseCellUnderTempRecThs() const
{
    return epsetCellUnderTempRecThs;
}

void DataProfile::setPseCellUnderTempRecThs(qint16 pseCellUnderTempRecThs)
{
    if (epsetCellUnderTempRecThs == pseCellUnderTempRecThs){ return; }

    epsetCellUnderTempRecThs = pseCellUnderTempRecThs;
    emit pseCellUnderTempRecThsChanged(epsetCellUnderTempRecThs);
}

quint16 DataProfile::getPseCellDiscDetThs() const
{
    return epsetCellDiscDetThs;
}

void DataProfile::setPseCellDiscDetThs(quint16 pseCellDiscDetThs)
{
    if (epsetCellDiscDetThs == pseCellDiscDetThs){ return; }

    epsetCellDiscDetThs = pseCellDiscDetThs;
    emit pseCellDiscDetThsChanged(epsetCellDiscDetThs);
}

quint8 DataProfile::getPseCellDiscDetTmo() const
{
    return epsetCellDiscDetTmo;
}

void DataProfile::setPseCellDiscDetTmo(quint8 pseCellDiscDetTmo)
{
    if (epsetCellDiscDetTmo == pseCellDiscDetTmo){ return; }

    epsetCellDiscDetTmo = pseCellDiscDetTmo;
    emit pseCellDiscDetTmoChanged(epsetCellDiscDetTmo);
}

quint16 DataProfile::getPseCellConnDetThs() const
{
    return epsetCellConnDetThs;
}

void DataProfile::setPseCellConnDetThs(quint16 pseCellConnDetThs)
{
    if (epsetCellConnDetThs == pseCellConnDetThs){ return; }

    epsetCellConnDetThs = pseCellConnDetThs;
    emit pseCellConnDetThsChanged(epsetCellConnDetThs);
}

quint8 DataProfile::getPseCellConnDetTmo() const
{
    return epsetCellConnDetTmo;
}

void DataProfile::setPseCellConnDetTmo(quint8 pseCellConnDetTmo)
{
    if (epsetCellConnDetTmo == pseCellConnDetTmo){ return; }

    epsetCellConnDetTmo = pseCellConnDetTmo;
    emit pseCellConnDetTmoChanged(epsetCellConnDetTmo);
}

quint16 DataProfile::getPseExceptionRecTmo() const
{
    return epsetExceptionRecTmo;
}

void DataProfile::setPseExceptionRecTmo(quint16 pseExceptionRecTmo)
{
    if (epsetExceptionRecTmo == pseExceptionRecTmo){ return; }

    epsetExceptionRecTmo = pseExceptionRecTmo;
    emit pseExceptionRecTmoChanged(epsetExceptionRecTmo);
}

quint8 DataProfile::getPseChgEventsDisable() const
{
    return epsetChgEventsDisable;
}

void DataProfile::setPseChgEventsDisable(quint8 pseChgEventsDisable)
{
    if (epsetChgEventsDisable == pseChgEventsDisable){ return; }

    epsetChgEventsDisable = pseChgEventsDisable;
    emit pseChgEventsDisableChanged(epsetChgEventsDisable);
}

quint16 DataProfile::getPseStateOfHealth() const
{
    return epsetStateOfHealth;
}

void DataProfile::setPseStateOfHealth(quint16 pseStateOfHealth)
{
    if (epsetStateOfHealth == pseStateOfHealth){ return; }

    epsetStateOfHealth = pseStateOfHealth;
    emit pseStateOfHealthChanged(epsetStateOfHealth);
}

quint32 DataProfile::getPseShBattNominalEnergy() const
{
    return epsetShBattNominalEnergy;
}

void DataProfile::setPseShBattNominalEnergy(quint32 pseShBattNominalEnergy)
{
    if (epsetShBattNominalEnergy == pseShBattNominalEnergy){ return; }

    epsetShBattNominalEnergy = pseShBattNominalEnergy;
    emit pseShBattNominalEnergyChanged(epsetShBattNominalEnergy);
}

quint8 DataProfile::getPseShBattSerialModules() const
{
    return epsetShBattSerialModules;
}

void DataProfile::setPseShBattSerialModules(quint8 pseShBattSerialModules)
{
    if (epsetShBattSerialModules == pseShBattSerialModules){ return; }

    epsetShBattSerialModules = pseShBattSerialModules;
    emit pseShBattSerialModulesChanged(epsetShBattSerialModules);
}

quint8 DataProfile::getPseEnMaxCurrentCtrl() const
{
    return epsetEnMaxCurrentCtrl;
}

void DataProfile::setPseEnMaxCurrentCtrl(quint8 pseEnMaxCurrentCtrl)
{
    if (epsetEnMaxCurrentCtrl == pseEnMaxCurrentCtrl){ return; }

    epsetEnMaxCurrentCtrl = pseEnMaxCurrentCtrl;
    emit pseEnMaxCurrentCtrlChanged(epsetEnMaxCurrentCtrl);
}

quint8 DataProfile::getPseMasterCellVCheckDisable() const
{
    return epsetMasterCellVCheckDisable;
}

void DataProfile::setPseMasterCellVCheckDisable(quint8 pseMasterCellVCheckDisable)
{
    if (epsetMasterCellVCheckDisable == pseMasterCellVCheckDisable){ return; }

    epsetMasterCellVCheckDisable = pseMasterCellVCheckDisable;
    emit pseMasterCellVCheckDisableChanged(epsetMasterCellVCheckDisable);
}

quint8 DataProfile::getPseMasterCellTCheckDisable() const
{
    return epsetMasterCellTCheckDisable;
}

void DataProfile::setPseMasterCellTCheckDisable(quint8 pseMasterCellTCheckDisable)
{
    if (epsetMasterCellTCheckDisable == pseMasterCellTCheckDisable){ return; }

    epsetMasterCellTCheckDisable = pseMasterCellTCheckDisable;
    emit pseMasterCellTCheckDisableChanged(epsetMasterCellTCheckDisable);
}

quint16 DataProfile::getPseCellResistance() const
{
    return epsetCellResistance;
}

void DataProfile::setPseCellResistance(quint16 pseCellResistance)
{
    if (epsetCellResistance == pseCellResistance){ return; }

    epsetCellResistance = pseCellResistance;
    emit pseCellResistanceChanged(epsetCellResistance);
}

quint8 DataProfile::getPseExtModuleType() const
{
    return epsetExtModuleType;
}

void DataProfile::setPseExtModuleType(quint8 pseExtModuleType)
{
    if (epsetExtModuleType == pseExtModuleType){ return; }

    epsetExtModuleType = pseExtModuleType;
    emit pseExtModuleTypeChanged(epsetExtModuleType);
}

quint16 DataProfile::getPseEcsLowChSens() const
{
    return epsetEcsLowChSens;
}

void DataProfile::setPseEcsLowChSens(quint16 pseEcsLowChSens)
{
    if (epsetEcsLowChSens == pseEcsLowChSens){ return; }

    epsetEcsLowChSens = pseEcsLowChSens;
    emit pseEcsLowChSensChanged(epsetEcsLowChSens);
}

quint16 DataProfile::getPseEcsHighChSens() const
{
    return epsetEcsHighChSens;
}

void DataProfile::setPseEcsHighChSens(quint16 pseEcsHighChSens)
{
    if (epsetEcsHighChSens == pseEcsHighChSens){ return; }

    epsetEcsHighChSens = pseEcsHighChSens;
    emit pseEcsHighChSensChanged(epsetEcsHighChSens);
}

quint8 DataProfile::getPseContinuousBalEnable() const
{
    return epsetContinuousBalEnable;
}

void DataProfile::setPseContinuousBalEnable(quint8 pseContinuousBalEnable)
{
    if (epsetContinuousBalEnable == pseContinuousBalEnable){ return; }

    epsetContinuousBalEnable = pseContinuousBalEnable;
    emit pseContinuousBalEnableChanged(epsetContinuousBalEnable);
}

quint16 DataProfile::getPseIcsSens() const
{
    return epsetIcsSens;
}

void DataProfile::setPseIcsSens(quint16 pseIcsSens)
{
    if (epsetIcsSens == pseIcsSens){ return; }

    epsetIcsSens = pseIcsSens;
    emit pseIcsSensChanged(epsetIcsSens);
}
