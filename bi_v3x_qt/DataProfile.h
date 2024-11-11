#ifndef DATAPROFILE_H
#define DATAPROFILE_H

#include <QObject>
#include "LiveData.h"
#include "SettingsDataMaster.h"

class DataProfile : public QObject
{
    Q_OBJECT
    // Live Data Master
    Q_PROPERTY(QVector<qreal> masterCellVolt READ getMasterCellVolt WRITE setMasterCellVolt NOTIFY masterCellVoltChanged)
    Q_PROPERTY(QVector<qreal> masterCellTemp READ getMasterCellTemp WRITE setMasterCellTemp NOTIFY masterCellTempChanged)
    Q_PROPERTY(QVector<qreal> masterBmsTemp READ getMasterBmsTemp WRITE setMasterBmsTemp NOTIFY masterBmsTempChanged)
    Q_PROPERTY(qreal masterMinCellVoltage READ getMasterMinCellVoltage WRITE setMasterMinCellVoltage NOTIFY masterMinCellVoltageChanged)
    Q_PROPERTY(qreal masterMaxCellVoltage READ getMasterMaxCellVoltage WRITE setMasterMaxCellVoltage NOTIFY masterMaxCellVoltageChanged)
    Q_PROPERTY(qreal masterMinCellTemp READ getMasterMinCellTemp WRITE setMasterMinCellTemp NOTIFY masterMinCellTempChanged)
    Q_PROPERTY(qreal masterMaxCellTemp READ getMasterMaxCellTemp WRITE setMasterMaxCellTemp NOTIFY masterMaxCellTempChanged)
    Q_PROPERTY(qreal masterMinBmsTemp READ getMasterMinBmsTemp WRITE setMasterMinBmsTemp NOTIFY masterMinBmsTempChanged)
    Q_PROPERTY(qreal masterMaxBmsTemp READ getMasterMaxBmsTemp WRITE setMasterMaxBmsTemp NOTIFY masterMaxBmsTempChanged)
    Q_PROPERTY(qreal masterModuleVoltage READ getMasterModuleVoltage WRITE setMasterModuleVoltage NOTIFY masterModuleVoltageChanged)
    Q_PROPERTY(quint16 masterBmsState READ getMasterBmsState WRITE setMasterBmsState NOTIFY masterBmsStateChanged)
    Q_PROPERTY(quint16 masterBalancingBits READ getMasterBalancingBits WRITE setMasterBalancingBits NOTIFY masterBalancingBitsChanged)
    Q_PROPERTY(quint16 masterBalancingDuration READ getMasterBalancingDuration WRITE setMasterBalancingDuration NOTIFY masterBalancingDurationChanged)
    Q_PROPERTY(quint32 masterLifeTimeCounter READ getMasterLifeTimeCounter WRITE setMasterLifeTimeCounter NOTIFY masterLifeTimeCounterChanged)
    Q_PROPERTY(quint16 masterPeriphStatus READ getMasterPeriphStatus WRITE setMasterPeriphStatus NOTIFY masterPeriphStatusChanged)

    // Live Data Battery
    Q_PROPERTY(qreal battVoltage READ getBattVoltage WRITE setBattVoltage NOTIFY battVoltageChanged)
    Q_PROPERTY(qreal battMinCellVoltage READ getBattMinCellVoltage WRITE setBattMinCellVoltage NOTIFY battMinCellVoltageChanged)
    Q_PROPERTY(qreal battMaxCellVoltage READ getBattMaxCellVoltage WRITE setBattMaxCellVoltage NOTIFY battMaxCellVoltageChanged)
    Q_PROPERTY(qreal battMinCellTemp READ getBattMinCellTemp WRITE setBattMinCellTemp NOTIFY battMinCellTempChanged)
    Q_PROPERTY(qreal battMaxCellTemp READ getBattMaxCellTemp WRITE setBattMaxCellTemp NOTIFY battMaxCellTempChanged)
    Q_PROPERTY(qreal battMinBmsTemp READ getBattMinBmsTemp WRITE setBattMinBmsTemp NOTIFY battMinBmsTempChanged)
    Q_PROPERTY(qreal battMaxBmsTemp READ getBattMaxBmsTemp WRITE setBattMaxBmsTemp NOTIFY battMaxBmsTempChanged)
    Q_PROPERTY(qreal battIntCurrent READ getBattIntCurrent WRITE setBattIntCurrent NOTIFY battIntCurrentChanged)
    Q_PROPERTY(qreal battIntCurrentAvg READ getBattIntCurrentAvg WRITE setBattIntCurrentAvg NOTIFY battIntCurrentAvgChanged)
    Q_PROPERTY(qreal battExtCurrent READ getBattExtCurrent WRITE setBattExtCurrent NOTIFY battExtCurrentChanged)
    Q_PROPERTY(qreal battExtCurrentAvg READ getBattExtCurrentAvg WRITE setBattExtCurrentAvg NOTIFY battExtCurrentAvgChanged)
    Q_PROPERTY(qreal battCurrent READ getBattCurrent WRITE setBattCurrent NOTIFY battCurrentChanged)
    Q_PROPERTY(qreal battCurrentAvg READ getBattCurrentAvg WRITE setBattCurrentAvg NOTIFY battCurrentAvgChanged)
    Q_PROPERTY(qreal battStateOfCharge READ getBattStateOfCharge WRITE setBattStateOfCharge NOTIFY battStateOfChargeChanged)
    Q_PROPERTY(qreal battStateOfHealth READ getBattStateOfHealth WRITE setBattStateOfHealth NOTIFY battStateOfHealthChanged)
    Q_PROPERTY(qreal battAvailableEnergy READ getBattAvailableEnergy WRITE setBattAvailableEnergy NOTIFY battAvailableEnergyChanged)
    Q_PROPERTY(qreal battMaxChgCurrent READ getBattMaxChgCurrent WRITE setBattMaxChgCurrent NOTIFY battMaxChgCurrentChanged)
    Q_PROPERTY(qreal battMaxDsgCurrent READ getBattMaxDsgCurrent WRITE setBattMaxDsgCurrent NOTIFY battMaxDsgCurrentChanged)
    Q_PROPERTY(qreal battResVoltage READ getBattResVoltage WRITE setBattResVoltage NOTIFY battResVoltageChanged)
    Q_PROPERTY(quint8 battSungrowStatus READ getBattSungrowStatus WRITE setBattSungrowStatus NOTIFY battSungrowStatusChanged)
    Q_PROPERTY(quint16 battExceptionL READ getBattExceptionL WRITE setBattExceptionL NOTIFY battExceptionLChanged)
    Q_PROPERTY(quint16 battExceptionM READ getBattExceptionM WRITE setBattExceptionM NOTIFY battExceptionMChanged)

    // Settings Master
    Q_PROPERTY(quint8 psCellsInSeriesMod READ getPsCellsInSeriesMod WRITE setPsCellsInSeriesMod NOTIFY psCellsInSeriesModChanged)
    Q_PROPERTY(quint16 psCellsInSeriesBatt READ getPsCellsInSeriesBatt WRITE setPsCellsInSeriesBatt NOTIFY psCellsInSeriesBattChanged)
    Q_PROPERTY(quint8 psModulesInSeries READ getPsModulesInSeries WRITE setPsModulesInSeries NOTIFY psModulesInSeriesChanged)
    Q_PROPERTY(quint16 psOverVoltageDetThreshold READ getPsOverVoltageDetThreshold WRITE setPsOverVoltageDetThreshold NOTIFY psOverVoltageDetThresholdChanged)
    Q_PROPERTY(quint16 psUnderVoltageDetThreshold READ getPsUnderVoltageDetThreshold WRITE setPsUnderVoltageDetThreshold NOTIFY psUnderVoltageDetThresholdChanged)
    Q_PROPERTY(quint16 psSlOverVoltageDetThreshold READ getPsSlOverVoltageDetThreshold WRITE setPsSlOverVoltageDetThreshold NOTIFY psSlOverVoltageDetThresholdChanged)
    Q_PROPERTY(quint16 psSlUnderVoltageDetThreshold READ getPsSlUnderVoltageDetThreshold WRITE setPsSlUnderVoltageDetThreshold NOTIFY psSlUnderVoltageDetThresholdChanged)
    Q_PROPERTY(quint16 psDsgOcDetThreshold READ getPsDsgOcDetThreshold WRITE setPsDsgOcDetThreshold NOTIFY psDsgOcDetThresholdChanged)
    Q_PROPERTY(quint16 psChgOcDetThreshold READ getPsChgOcDetThreshold WRITE setPsChgOcDetThreshold NOTIFY psChgOcDetThresholdChanged)
    Q_PROPERTY(quint8 psOperatingMode READ getPsOperatingMode WRITE setPsOperatingMode NOTIFY psOperatingModeChanged)
    Q_PROPERTY(quint8 psMasterSlaveCommMode READ getPsMasterSlaveCommMode WRITE setPsMasterSlaveCommMode NOTIFY psMasterSlaveCommModeChanged)
    Q_PROPERTY(quint8 psDpDsgSwitchType READ getPsDpDsgSwitchType WRITE setPsDpDsgSwitchType NOTIFY psDpDsgSwitchTypeChanged)
    Q_PROPERTY(quint8 psDpChgSwitchType READ getPsDpChgSwitchType WRITE setPsDpChgSwitchType NOTIFY psDpChgSwitchTypeChanged)
    Q_PROPERTY(quint8 psSpSwitchType READ getPsSpSwitchType WRITE setPsSpSwitchType NOTIFY psSpSwitchTypeChanged)
    Q_PROPERTY(quint8 psSpSwitchMonitorType READ getPsSpSwitchMonitorType WRITE setPsSpSwitchMonitorType NOTIFY psSpSwitchMonitorTypeChanged)
    Q_PROPERTY(quint8 psPreDsgSwitchType READ getPsPreDsgSwitchType WRITE setPsPreDsgSwitchType NOTIFY psPreDsgSwitchTypeChanged)
    Q_PROPERTY(quint8 psPreDsgSwitchDuration READ getPsPreDsgSwitchDuration WRITE setPsPreDsgSwitchDuration NOTIFY psPreDsgSwitchDurationChanged)
    Q_PROPERTY(quint8 psIgnitionType READ getPsIgnitionType WRITE setPsIgnitionType NOTIFY psIgnitionTypeChanged)
    Q_PROPERTY(quint8 psChgDetectionType READ getPsChgDetectionType WRITE setPsChgDetectionType NOTIFY psChgDetectionTypeChanged)
    Q_PROPERTY(quint8 psChgIntDetectionHighThreshold READ getPsChgIntDetectionHighThreshold WRITE setPsChgIntDetectionHighThreshold NOTIFY psChgIntDetectionHighThresholdChanged)
    Q_PROPERTY(quint8 psChgIntDetectionLowThreshold READ getPsChgIntDetectionLowThreshold WRITE setPsChgIntDetectionLowThreshold NOTIFY psChgIntDetectionLowThresholdChanged)
    Q_PROPERTY(quint8 psDsgDetectionType READ getPsDsgDetectionType WRITE setPsDsgDetectionType NOTIFY psDsgDetectionTypeChanged)
    Q_PROPERTY(quint8 psDsgIntDetectionThreshold READ getPsDsgIntDetectionThreshold WRITE setPsDsgIntDetectionThreshold NOTIFY psDsgIntDetectionThresholdChanged)
    Q_PROPERTY(quint8 psChargerType READ getPsChargerType WRITE setPsChargerType NOTIFY psChargerTypeChanged)
    Q_PROPERTY(quint16 psEarlyBalancingThs READ getPsEarlyBalancingThs WRITE setPsEarlyBalancingThs NOTIFY psEarlyBalancingThsChanged)
    Q_PROPERTY(quint16 psCellsAllowedDisbalance READ getPsCellsAllowedDisbalance WRITE setPsCellsAllowedDisbalance NOTIFY psCellsAllowedDisbalanceChanged)
    Q_PROPERTY(quint16 psChgCompleteCurrent READ getPsChgCompleteCurrent WRITE setPsChgCompleteCurrent NOTIFY psChgCompleteCurrentChanged)
    Q_PROPERTY(quint16 psDsgCompleteCurrent READ getPsDsgCompleteCurrent WRITE setPsDsgCompleteCurrent NOTIFY psDsgCompleteCurrentChanged)
    Q_PROPERTY(quint8 psChgConnectionTmo READ getPsChgConnectionTmo WRITE setPsChgConnectionTmo NOTIFY psChgConnectionTmoChanged)
    Q_PROPERTY(quint8 psDsgConnectionTmo READ getPsDsgConnectionTmo WRITE setPsDsgConnectionTmo NOTIFY psDsgConnectionTmoChanged)
    Q_PROPERTY(quint32 psBatteryCapacity READ getPsBatteryCapacity WRITE setPsBatteryCapacity NOTIFY psBatteryCapacityChanged)
    Q_PROPERTY(quint16 psStateOfCharge READ getPsStateOfCharge WRITE setPsStateOfCharge NOTIFY psStateOfChargeChanged)
    Q_PROPERTY(quint16 psFullyChgVoltageDetThs READ getPsFullyChgVoltageDetThs WRITE setPsFullyChgVoltageDetThs NOTIFY psFullyChgVoltageDetThsChanged)
    Q_PROPERTY(quint16 psFullyChgVoltageRecThs READ getPsFullyChgVoltageRecThs WRITE setPsFullyChgVoltageRecThs NOTIFY psFullyChgVoltageRecThsChanged)
    Q_PROPERTY(quint16 psFullyChgVoltageTolerance READ getPsFullyChgVoltageTolerance WRITE setPsFullyChgVoltageTolerance NOTIFY psFullyChgVoltageToleranceChanged)
    Q_PROPERTY(quint8 psFullyChgSwitchCtrlDisable READ getPsFullyChgSwitchCtrlDisable WRITE setPsFullyChgSwitchCtrlDisable NOTIFY psFullyChgSwitchCtrlDisableChanged)
    Q_PROPERTY(quint16 psAiInHighThreshold READ getPsAiInHighThreshold WRITE setPsAiInHighThreshold NOTIFY psAiInHighThresholdChanged)
    Q_PROPERTY(quint16 psAiInLowThreshold READ getPsAiInLowThreshold WRITE setPsAiInLowThreshold NOTIFY psAiInLowThresholdChanged)
    Q_PROPERTY(quint16 psExtOutputOCTmo READ getPsExtOutputOCTmo WRITE setPsExtOutputOCTmo NOTIFY psExtOutputOCTmoChanged)
    Q_PROPERTY(quint16 psExtOutputOCRecTmo READ getPsExtOutputOCRecTmo WRITE setPsExtOutputOCRecTmo NOTIFY psExtOutputOCRecTmoChanged)
    Q_PROPERTY(quint8 psExtNtcSensorType READ getPsExtNtcSensorType WRITE setPsExtNtcSensorType NOTIFY psExtNtcSensorTypeChanged)
    Q_PROPERTY(quint8 psExtNtcSensorEnStatus READ getPsExtNtcSensorEnStatus WRITE setPsExtNtcSensorEnStatus NOTIFY psExtNtcSensorEnStatusChanged)
    Q_PROPERTY(quint8 psExtCurrentSensorType READ getPsExtCurrentSensorType WRITE setPsExtCurrentSensorType NOTIFY psExtCurrentSensorTypeChanged)
    Q_PROPERTY(quint8 psExtCurrentSensorInvert READ getPsExtCurrentSensorInvert WRITE setPsExtCurrentSensorInvert NOTIFY psExtCurrentSensorInvertChanged)
    Q_PROPERTY(quint8 psCurrentAvgLevel READ getPsCurrentAvgLevel WRITE setPsCurrentAvgLevel NOTIFY psCurrentAvgLevelChanged)
    Q_PROPERTY(quint8 psSwDiagnosticsDisable READ getPsSwDiagnosticsDisable WRITE setPsSwDiagnosticsDisable NOTIFY psSwDiagnosticsDisableChanged)
    Q_PROPERTY(quint8 pseFullyDsgSwitchCtrlDisable READ getPseFullyDsgSwitchCtrlDisable WRITE setPseFullyDsgSwitchCtrlDisable NOTIFY pseFullyDsgSwitchCtrlDisableChanged)
    Q_PROPERTY(quint16 pseOverVoltageDetThs READ getPseOverVoltageDetThs WRITE setPseOverVoltageDetThs NOTIFY pseOverVoltageDetThsChanged)
    Q_PROPERTY(quint16 pseOverVoltageRecThs READ getPseOverVoltageRecThs WRITE setPseOverVoltageRecThs NOTIFY pseOverVoltageRecThsChanged)
    Q_PROPERTY(quint16 pseFullyDsgVoltageDetThs READ getPseFullyDsgVoltageDetThs WRITE setPseFullyDsgVoltageDetThs NOTIFY pseFullyDsgVoltageDetThsChanged)
    Q_PROPERTY(quint16 pseFullyDsgVoltageRecThs READ getPseFullyDsgVoltageRecThs WRITE setPseFullyDsgVoltageRecThs NOTIFY pseFullyDsgVoltageRecThsChanged)
    Q_PROPERTY(quint16 pseUnderVoltageDetThs READ getPseUnderVoltageDetThs WRITE setPseUnderVoltageDetThs NOTIFY pseUnderVoltageDetThsChanged)
    Q_PROPERTY(quint16 pseUnderVoltageRecThs READ getPseUnderVoltageRecThs WRITE setPseUnderVoltageRecThs NOTIFY pseUnderVoltageRecThsChanged)
    Q_PROPERTY(quint16 pseDsgOverCurrentDetThs1 READ getPseDsgOverCurrentDetThs1 WRITE setPseDsgOverCurrentDetThs1 NOTIFY pseDsgOverCurrentDetThs1Changed)
    Q_PROPERTY(quint16 pseDsgOverCurrentDetThs2 READ getPseDsgOverCurrentDetThs2 WRITE setPseDsgOverCurrentDetThs2 NOTIFY pseDsgOverCurrentDetThs2Changed)
    Q_PROPERTY(quint16 pseDsgOverCurrentDetTmo1 READ getPseDsgOverCurrentDetTmo1 WRITE setPseDsgOverCurrentDetTmo1 NOTIFY pseDsgOverCurrentDetTmo1Changed)
    Q_PROPERTY(quint16 pseDsgOverCurrentDetTmo2 READ getPseDsgOverCurrentDetTmo2 WRITE setPseDsgOverCurrentDetTmo2 NOTIFY pseDsgOverCurrentDetTmo2Changed)
    Q_PROPERTY(quint16 pseRegOverCurrentDetThs1 READ getPseRegOverCurrentDetThs1 WRITE setPseRegOverCurrentDetThs1 NOTIFY pseRegOverCurrentDetThs1Changed)
    Q_PROPERTY(quint16 pseRegOverCurrentDetThs2 READ getPseRegOverCurrentDetThs2 WRITE setPseRegOverCurrentDetThs2 NOTIFY pseRegOverCurrentDetThs2Changed)
    Q_PROPERTY(quint16 pseRegOverCurrentDetTmo1 READ getPseRegOverCurrentDetTmo1 WRITE setPseRegOverCurrentDetTmo1 NOTIFY pseRegOverCurrentDetTmo1Changed)
    Q_PROPERTY(quint16 pseRegOverCurrentDetTmo2 READ getPseRegOverCurrentDetTmo2 WRITE setPseRegOverCurrentDetTmo2 NOTIFY pseRegOverCurrentDetTmo2Changed)
    Q_PROPERTY(quint16 pseChgOverCurrentDetThs1 READ getPseChgOverCurrentDetThs1 WRITE setPseChgOverCurrentDetThs1 NOTIFY pseChgOverCurrentDetThs1Changed)
    Q_PROPERTY(quint16 pseChgOverCurrentDetThs2 READ getPseChgOverCurrentDetThs2 WRITE setPseChgOverCurrentDetThs2 NOTIFY pseChgOverCurrentDetThs2Changed)
    Q_PROPERTY(quint16 pseChgOverCurrentDetTmo1 READ getPseChgOverCurrentDetTmo1 WRITE setPseChgOverCurrentDetTmo1 NOTIFY pseChgOverCurrentDetTmo1Changed)
    Q_PROPERTY(quint16 pseChgOverCurrentDetTmo2 READ getPseChgOverCurrentDetTmo2 WRITE setPseChgOverCurrentDetTmo2 NOTIFY pseChgOverCurrentDetTmo2Changed)
    Q_PROPERTY(qint16 pseCellOverTempDetThs READ getPseCellOverTempDetThs WRITE setPseCellOverTempDetThs NOTIFY pseCellOverTempDetThsChanged)
    Q_PROPERTY(qint16 pseCellOverTempRecThs READ getPseCellOverTempRecThs WRITE setPseCellOverTempRecThs NOTIFY pseCellOverTempRecThsChanged)
    Q_PROPERTY(qint16 pseCellChgUnderTempDetThs READ getPseCellChgUnderTempDetThs WRITE setPseCellChgUnderTempDetThs NOTIFY pseCellChgUnderTempDetThsChanged)
    Q_PROPERTY(qint16 pseCellChgUnderTempRecThs READ getPseCellChgUnderTempRecThs WRITE setPseCellChgUnderTempRecThs NOTIFY pseCellChgUnderTempRecThsChanged)
    Q_PROPERTY(qint16 pseCellUnderTempDetThs READ getPseCellUnderTempDetThs WRITE setPseCellUnderTempDetThs NOTIFY pseCellUnderTempDetThsChanged)
    Q_PROPERTY(qint16 pseCellUnderTempRecThs READ getPseCellUnderTempRecThs WRITE setPseCellUnderTempRecThs NOTIFY pseCellUnderTempRecThsChanged)
    Q_PROPERTY(quint16 pseCellDiscDetThs READ getPseCellDiscDetThs WRITE setPseCellDiscDetThs NOTIFY pseCellDiscDetThsChanged)
    Q_PROPERTY(quint8 pseCellDiscDetTmo READ getPseCellDiscDetTmo WRITE setPseCellDiscDetTmo NOTIFY pseCellDiscDetTmoChanged)
    Q_PROPERTY(quint16 pseCellConnDetThs READ getPseCellConnDetThs WRITE setPseCellConnDetThs NOTIFY pseCellConnDetThsChanged)
    Q_PROPERTY(quint8 pseCellConnDetTmo READ getPseCellConnDetTmo WRITE setPseCellConnDetTmo NOTIFY pseCellConnDetTmoChanged)
    Q_PROPERTY(quint16 pseExceptionRecTmo READ getPseExceptionRecTmo WRITE setPseExceptionRecTmo NOTIFY pseExceptionRecTmoChanged)
    Q_PROPERTY(quint8 pseChgEventsDisable READ getPseChgEventsDisable WRITE setPseChgEventsDisable NOTIFY pseChgEventsDisableChanged)
    Q_PROPERTY(quint16 pseStateOfHealth READ getPseStateOfHealth WRITE setPseStateOfHealth NOTIFY pseStateOfHealthChanged)
    Q_PROPERTY(quint32 pseShBattNominalEnergy READ getPseShBattNominalEnergy WRITE setPseShBattNominalEnergy NOTIFY pseShBattNominalEnergyChanged)
    Q_PROPERTY(quint8 pseShBattSerialModules READ getPseShBattSerialModules WRITE setPseShBattSerialModules NOTIFY pseShBattSerialModulesChanged)
    Q_PROPERTY(quint8 pseEnMaxCurrentCtrl READ getPseEnMaxCurrentCtrl WRITE setPseEnMaxCurrentCtrl NOTIFY pseEnMaxCurrentCtrlChanged)
    Q_PROPERTY(quint8 pseMasterCellVCheckDisable READ getPseMasterCellVCheckDisable WRITE setPseMasterCellVCheckDisable NOTIFY pseMasterCellVCheckDisableChanged)
    Q_PROPERTY(quint8 pseMasterCellTCheckDisable READ getPseMasterCellTCheckDisable WRITE setPseMasterCellTCheckDisable NOTIFY pseMasterCellTCheckDisableChanged)
    Q_PROPERTY(quint16 pseCellResistance READ getPseCellResistance WRITE setPseCellResistance NOTIFY pseCellResistanceChanged)
    Q_PROPERTY(quint8 pseExtModuleType READ getPseExtModuleType WRITE setPseExtModuleType NOTIFY pseExtModuleTypeChanged)
    Q_PROPERTY(quint16 pseEcsLowChSens READ getPseEcsLowChSens WRITE setPseEcsLowChSens NOTIFY pseEcsLowChSensChanged)
    Q_PROPERTY(quint16 pseEcsHighChSens READ getPseEcsHighChSens WRITE setPseEcsHighChSens NOTIFY pseEcsHighChSensChanged)
    Q_PROPERTY(quint8 pseContinuousBalEnable READ getPseContinuousBalEnable WRITE setPseContinuousBalEnable NOTIFY pseContinuousBalEnableChanged)
    Q_PROPERTY(quint16 pseIcsSens READ getPseIcsSens WRITE setPseIcsSens NOTIFY pseIcsSensChanged)

public:
    explicit DataProfile(QObject *parent = nullptr);

    // Live Data Master
    QVector<qreal> getMasterCellVolt() const;
    void setMasterCellVolt(QVector<qreal> masterCellVolt);
    QVector<qreal> getMasterCellTemp() const;
    void setMasterCellTemp(QVector<qreal> masterCellTemp);
    QVector<qreal> getMasterBmsTemp() const;
    void setMasterBmsTemp(QVector<qreal> masterBmsTemp);
    qreal getMasterMinCellVoltage() const;
    void setMasterMinCellVoltage(qreal masterMinCellVoltage);
    qreal getMasterMaxCellVoltage() const;
    void setMasterMaxCellVoltage(qreal masterMaxCellVoltage);
    qreal getMasterMinCellTemp() const;
    void setMasterMinCellTemp(qreal masterMinCellTemp);
    qreal getMasterMaxCellTemp() const;
    void setMasterMaxCellTemp(qreal masterMaxCellTemp);
    qreal getMasterMinBmsTemp() const;
    void setMasterMinBmsTemp(qreal masterMinBmsTemp);
    qreal getMasterMaxBmsTemp() const;
    void setMasterMaxBmsTemp(qreal masterMaxBmsTemp);
    qreal getMasterModuleVoltage() const;
    void setMasterModuleVoltage(qreal masterModuleVoltage);
    quint16 getMasterBmsState() const;
    void setMasterBmsState(quint16 masterBmsState);
    quint16 getMasterBalancingBits() const;
    void setMasterBalancingBits(quint16 masterBalancingBits);
    quint16 getMasterBalancingDuration() const;
    void setMasterBalancingDuration(quint16 masterBalancingDuration);
    quint32 getMasterLifeTimeCounter() const;
    void setMasterLifeTimeCounter(quint32 masterLifeTimeCounter);
    quint16 getMasterPeriphStatus() const;
    void setMasterPeriphStatus(quint16 masterPeriphStatus);

    // Live Data Battery
    qreal getBattVoltage() const;
    void setBattVoltage(qreal battVoltage);
    qreal getBattMinCellVoltage() const;
    void setBattMinCellVoltage(qreal battMinCellVoltage);
    qreal getBattMaxCellVoltage() const;
    void setBattMaxCellVoltage(qreal battMaxCellVoltage);
    qreal getBattMinCellTemp() const;
    void setBattMinCellTemp(qreal battMinCellTemp);
    qreal getBattMaxCellTemp() const;
    void setBattMaxCellTemp(qreal battMaxCellTemp);
    qreal getBattMinBmsTemp() const;
    void setBattMinBmsTemp(qreal battMinBmsTemp);
    qreal getBattMaxBmsTemp() const;
    void setBattMaxBmsTemp(qreal battMaxBmsTemp);
    qreal getBattIntCurrent() const;
    void setBattIntCurrent(qreal battIntCurrent);
    qreal getBattIntCurrentAvg() const;
    void setBattIntCurrentAvg(qreal battIntCurrentAvg);
    qreal getBattExtCurrent() const;
    void setBattExtCurrent(qreal battExtCurrent);
    qreal getBattExtCurrentAvg() const;
    void setBattExtCurrentAvg(qreal battExtCurrentAvg);
    qreal getBattCurrent() const;
    void setBattCurrent(qreal battCurrent);
    qreal getBattCurrentAvg() const;
    void setBattCurrentAvg(qreal battCurrentAvg);
    qreal getBattStateOfCharge() const;
    void setBattStateOfCharge(qreal battStateOfCharge);
    qreal getBattStateOfHealth() const;
    void setBattStateOfHealth(qreal battStateOfHealth);
    qreal getBattAvailableEnergy() const;
    void setBattAvailableEnergy(qreal battAvailableEnergy);
    qreal getBattMaxChgCurrent() const;
    void setBattMaxChgCurrent(qreal battMaxChgCurrent);
    qreal getBattMaxDsgCurrent() const;
    void setBattMaxDsgCurrent(qreal battMaxDsgCurrent);
    qreal getBattResVoltage() const;
    void setBattResVoltage(qreal battResVoltage);
    quint8 getBattSungrowStatus() const;
    void setBattSungrowStatus(quint8 battSungrowStatus);
    quint16 getBattExceptionL() const;
    void setBattExceptionL(quint16 battExceptionL);
    quint16 getBattExceptionM() const;
    void setBattExceptionM(quint16 battExceptionM);

    // Settings Master
    quint8 getPsCellsInSeriesMod() const;
    void setPsCellsInSeriesMod(quint8 psCellsInSeriesMod);
    quint16 getPsCellsInSeriesBatt() const;
    void setPsCellsInSeriesBatt(quint16 psCellsInSeriesBatt);
    quint8 getPsModulesInSeries() const;
    void setPsModulesInSeries(quint8 psModulesInSeries);
    quint16 getPsOverVoltageDetThreshold() const;
    void setPsOverVoltageDetThreshold(quint16 psOverVoltageDetThreshold);
    quint16 getPsUnderVoltageDetThreshold() const;
    void setPsUnderVoltageDetThreshold(quint16 psUnderVoltageDetThreshold);
    quint16 getPsSlOverVoltageDetThreshold() const;
    void setPsSlOverVoltageDetThreshold(quint16 psSlOverVoltageDetThreshold);
    quint16 getPsSlUnderVoltageDetThreshold() const;
    void setPsSlUnderVoltageDetThreshold(quint16 psSlUnderVoltageDetThreshold);
    quint16 getPsDsgOcDetThreshold() const;
    void setPsDsgOcDetThreshold(quint16 psDsgOcDetThreshold);
    quint16 getPsChgOcDetThreshold() const;
    void setPsChgOcDetThreshold(quint16 psChgOcDetThreshold);
    quint8 getPsOperatingMode() const;
    void setPsOperatingMode(quint8 psOperatingMode);
    quint8 getPsMasterSlaveCommMode() const;
    void setPsMasterSlaveCommMode(quint8 psMasterSlaveCommMode);
    quint8 getPsDpDsgSwitchType() const;
    void setPsDpDsgSwitchType(quint8 psDpDsgSwitchType);
    quint8 getPsDpChgSwitchType() const;
    void setPsDpChgSwitchType(quint8 psDpChgSwitchType);
    quint8 getPsSpSwitchType() const;
    void setPsSpSwitchType(quint8 psSpSwitchType);
    quint8 getPsSpSwitchMonitorType() const;
    void setPsSpSwitchMonitorType(quint8 psSpSwitchMonitorType);
    quint8 getPsPreDsgSwitchType() const;
    void setPsPreDsgSwitchType(quint8 psPreDsgSwitchType);
    quint8 getPsPreDsgSwitchDuration() const;
    void setPsPreDsgSwitchDuration(quint8 psPreDsgSwitchDuration);
    quint8 getPsIgnitionType() const;
    void setPsIgnitionType(quint8 psIgnitionType);
    quint8 getPsChgDetectionType() const;
    void setPsChgDetectionType(quint8 psChgDetectionType);
    quint8 getPsChgIntDetectionHighThreshold() const;
    void setPsChgIntDetectionHighThreshold(quint8 psChgIntDetectionHighThreshold);
    quint8 getPsChgIntDetectionLowThreshold() const;
    void setPsChgIntDetectionLowThreshold(quint8 psChgIntDetectionLowThreshold);
    quint8 getPsDsgDetectionType() const;
    void setPsDsgDetectionType(quint8 psDsgDetectionType);
    quint8 getPsDsgIntDetectionThreshold() const;
    void setPsDsgIntDetectionThreshold(quint8 psDsgIntDetectionThreshold);
    quint8 getPsChargerType() const;
    void setPsChargerType(quint8 psChargerType);
    quint16 getPsEarlyBalancingThs() const;
    void setPsEarlyBalancingThs(quint16 psEarlyBalancingThs);
    quint16 getPsCellsAllowedDisbalance() const;
    void setPsCellsAllowedDisbalance(quint16 psCellsAllowedDisbalance);
    quint16 getPsChgCompleteCurrent() const;
    void setPsChgCompleteCurrent(quint16 psChgCompleteCurrent);
    quint16 getPsDsgCompleteCurrent() const;
    void setPsDsgCompleteCurrent(quint16 psDsgCompleteCurrent);
    quint8 getPsChgConnectionTmo() const;
    void setPsChgConnectionTmo(quint8 psChgConnectionTmo);
    quint8 getPsDsgConnectionTmo() const;
    void setPsDsgConnectionTmo(quint8 psDsgConnectionTmo);
    quint32 getPsBatteryCapacity() const;
    void setPsBatteryCapacity(quint32 psBatteryCapacity);
    quint16 getPsStateOfCharge() const;
    void setPsStateOfCharge(quint16 psStateOfCharge);
    quint16 getPsFullyChgVoltageDetThs() const;
    void setPsFullyChgVoltageDetThs(quint16 psFullyChgVoltageDetThs);
    quint16 getPsFullyChgVoltageRecThs() const;
    void setPsFullyChgVoltageRecThs(quint16 psFullyChgVoltageRecThs);
    quint16 getPsFullyChgVoltageTolerance() const;
    void setPsFullyChgVoltageTolerance(quint16 psFullyChgVoltageTolerance);
    quint8 getPsFullyChgSwitchCtrlDisable() const;
    void setPsFullyChgSwitchCtrlDisable(quint8 psFullyChgSwitchCtrlDisable);
    quint16 getPsAiInHighThreshold() const;
    void setPsAiInHighThreshold(quint16 psAiInHighThreshold);
    quint16 getPsAiInLowThreshold() const;
    void setPsAiInLowThreshold(quint16 psAiInLowThreshold);
    quint16 getPsExtOutputOCTmo() const;
    void setPsExtOutputOCTmo(quint16 psExtOutputOCTmo);
    quint16 getPsExtOutputOCRecTmo() const;
    void setPsExtOutputOCRecTmo(quint16 psExtOutputOCRecTmo);
    quint8 getPsExtNtcSensorType() const;
    void setPsExtNtcSensorType(quint8 psExtNtcSensorType);
    quint8 getPsExtNtcSensorEnStatus() const;
    void setPsExtNtcSensorEnStatus(quint8 psExtNtcSensorEnStatus);
    quint8 getPsExtCurrentSensorType() const;
    void setPsExtCurrentSensorType(quint8 psExtCurrentSensorType);
    quint8 getPsExtCurrentSensorInvert() const;
    void setPsExtCurrentSensorInvert(quint8 psExtCurrentSensorInvert);
    quint8 getPsCurrentAvgLevel() const;
    void setPsCurrentAvgLevel(quint8 psCurrentAvgLevel);
    quint8 getPsSwDiagnosticsDisable() const;
    void setPsSwDiagnosticsDisable(quint8 psSwDiagnosticsDisable);
    quint8 getPseFullyDsgSwitchCtrlDisable() const;
    void setPseFullyDsgSwitchCtrlDisable(quint8 pseFullyDsgSwitchCtrlDisable); 
    quint16 getPseOverVoltageDetThs() const;
    void setPseOverVoltageDetThs(quint16 pseOverVoltageDetThs);
    quint16 getPseOverVoltageRecThs() const;
    void setPseOverVoltageRecThs(quint16 pseOverVoltageRecThs);
    quint16 getPseFullyDsgVoltageDetThs() const;
    void setPseFullyDsgVoltageDetThs(quint16 pseFullyDsgVoltageDetThs);
    quint16 getPseFullyDsgVoltageRecThs() const;
    void setPseFullyDsgVoltageRecThs(quint16 pseFullyDsgVoltageRecThs);
    quint16 getPseUnderVoltageDetThs() const;
    void setPseUnderVoltageDetThs(quint16 pseUnderVoltageDetThs);
    quint16 getPseUnderVoltageRecThs() const;
    void setPseUnderVoltageRecThs(quint16 pseUnderVoltageRecThs);
    quint16 getPseDsgOverCurrentDetThs1() const;
    void setPseDsgOverCurrentDetThs1(quint16 pseDsgOverCurrentDetThs1);
    quint16 getPseDsgOverCurrentDetThs2() const;
    void setPseDsgOverCurrentDetThs2(quint16 pseDsgOverCurrentDetThs2);
    quint16 getPseDsgOverCurrentDetTmo1() const;
    void setPseDsgOverCurrentDetTmo1(quint16 pseDsgOverCurrentDetTmo1);
    quint16 getPseDsgOverCurrentDetTmo2() const;
    void setPseDsgOverCurrentDetTmo2(quint16 pseDsgOverCurrentDetTmo2);
    quint16 getPseRegOverCurrentDetThs1() const;
    void setPseRegOverCurrentDetThs1(quint16 pseRegOverCurrentDetThs1);
    quint16 getPseRegOverCurrentDetThs2() const;
    void setPseRegOverCurrentDetThs2(quint16 pseRegOverCurrentDetThs2);
    quint16 getPseRegOverCurrentDetTmo1() const;
    void setPseRegOverCurrentDetTmo1(quint16 pseRegOverCurrentDetTmo1);
    quint16 getPseRegOverCurrentDetTmo2() const;
    void setPseRegOverCurrentDetTmo2(quint16 pseRegOverCurrentDetTmo2);
    quint16 getPseChgOverCurrentDetThs1() const;
    void setPseChgOverCurrentDetThs1(quint16 pseChgOverCurrentDetThs1);
    quint16 getPseChgOverCurrentDetThs2() const;
    void setPseChgOverCurrentDetThs2(quint16 pseChgOverCurrentDetThs2);
    quint16 getPseChgOverCurrentDetTmo1() const;
    void setPseChgOverCurrentDetTmo1(quint16 pseChgOverCurrentDetTmo1);
    quint16 getPseChgOverCurrentDetTmo2() const;
    void setPseChgOverCurrentDetTmo2(quint16 pseChgOverCurrentDetTmo2);
    qint16 getPseCellOverTempDetThs() const;
    void setPseCellOverTempDetThs(qint16 pseCellOverTempDetThs);
    qint16 getPseCellOverTempRecThs() const;
    void setPseCellOverTempRecThs(qint16 pseCellOverTempRecThs);
    qint16 getPseCellChgUnderTempDetThs() const;
    void setPseCellChgUnderTempDetThs(qint16 pseCellChgUnderTempDetThs);
    qint16 getPseCellChgUnderTempRecThs() const;
    void setPseCellChgUnderTempRecThs(qint16 pseCellChgUnderTempRecThs);
    qint16 getPseCellUnderTempDetThs() const;
    void setPseCellUnderTempDetThs(qint16 pseCellUnderTempDetThs);
    qint16 getPseCellUnderTempRecThs() const;
    void setPseCellUnderTempRecThs(qint16 pseCellUnderTempRecThs);
    quint16 getPseCellDiscDetThs() const;
    void setPseCellDiscDetThs(quint16 pseCellDiscDetThs);
    quint8 getPseCellDiscDetTmo() const;
    void setPseCellDiscDetTmo(quint8 pseCellDiscDetTmo);
    quint16 getPseCellConnDetThs() const;
    void setPseCellConnDetThs(quint16 pseCellConnDetThs);
    quint8 getPseCellConnDetTmo() const;
    void setPseCellConnDetTmo(quint8 pseCellConnDetTmo);
    quint16 getPseExceptionRecTmo() const;
    void setPseExceptionRecTmo(quint16 pseExceptionRecTmo);
    quint8 getPseChgEventsDisable() const;
    void setPseChgEventsDisable(quint8 pseChgEventsDisable);
    quint16 getPseStateOfHealth() const;
    void setPseStateOfHealth(quint16 pseStateOfHealth);
    quint32 getPseShBattNominalEnergy() const;
    void setPseShBattNominalEnergy(quint32 pseShBattNominalEnergy);
    quint8 getPseShBattSerialModules() const;
    void setPseShBattSerialModules(quint8 pseShBattSerialModules);
    quint8 getPseEnMaxCurrentCtrl() const;
    void setPseEnMaxCurrentCtrl(quint8 pseEnMaxCurrentCtrl);
    quint8 getPseMasterCellVCheckDisable() const;
    void setPseMasterCellVCheckDisable(quint8 pseMasterCellVCheckDisable);
    quint8 getPseMasterCellTCheckDisable() const;
    void setPseMasterCellTCheckDisable(quint8 pseMasterCellTCheckDisable);
    quint16 getPseCellResistance() const;
    void setPseCellResistance(quint16 pseCellResistance);
    quint8 getPseExtModuleType() const;
    void setPseExtModuleType(quint8 pseExtModuleType);
    quint16 getPseEcsLowChSens() const;
    void setPseEcsLowChSens(quint16 pseEcsLowChSens);
    quint16 getPseEcsHighChSens() const;
    void setPseEcsHighChSens(quint16 pseEcsHighChSens);
    quint8 getPseContinuousBalEnable() const;
    void setPseContinuousBalEnable(quint8 pseContinuousBalEnable);
    quint16 getPseIcsSens() const;
    void setPseIcsSens(quint16 pseIcsSens);

public slots:
    void updateLiveData(LiveData &liveData);
    void updateSettingsDataMaster(SettingsDataMaster &settingsDataMaster);

signals:
    // Live Data Master
    void masterCellVoltChanged(QVector<qreal> masterCellVolt);
    void masterCellTempChanged(QVector<qreal> masterCellTemp);
    void masterBmsTempChanged(QVector<qreal> masterBmsTemp);
    void masterMinCellVoltageChanged(qreal masterMinCellVoltage);
    void masterMaxCellVoltageChanged(qreal masterMaxCellVoltage);
    void masterMinCellTempChanged(qreal masterMinCellTemp);
    void masterMaxCellTempChanged(qreal masterMaxCellTemp);
    void masterMinBmsTempChanged(qreal masterMinBmsTemp);
    void masterMaxBmsTempChanged(qreal masterMaxBmsTemp);
    void masterModuleVoltageChanged(qreal masterModuleVoltage);
    void masterBmsStateChanged(quint16 masterBmsState);
    void masterBalancingBitsChanged(quint16 masterBalancingBits);
    void masterBalancingDurationChanged(quint16 masterBalancingDuration);
    void masterLifeTimeCounterChanged(quint32 masterLifeTimeCounter);
    void masterPeriphStatusChanged(quint16 masterPeriphStatus);

    // Live Data Battery
    void battVoltageChanged(qreal battVoltage);
    void battMinCellVoltageChanged(qreal battMinCellVoltage);
    void battMaxCellVoltageChanged(qreal battMaxCellVoltage);
    void battMinCellTempChanged(qreal battMinCellTemp);
    void battMaxCellTempChanged(qreal battMaxCellTemp);
    void battMinBmsTempChanged(qreal battMinBmsTemp);
    void battMaxBmsTempChanged(qreal battMaxBmsTemp);
    void battIntCurrentChanged(qreal battIntCurrent);
    void battIntCurrentAvgChanged(qreal battIntCurrentAvg);
    void battExtCurrentChanged(qreal battExtCurrent);
    void battExtCurrentAvgChanged(qreal battExtCurrentAvg);
    void battCurrentChanged(qreal battCurrent);
    void battCurrentAvgChanged(qreal battCurrentAvg);
    void battStateOfChargeChanged(qreal battStateOfCharge);
    void battStateOfHealthChanged(qreal battStateOfHealth);
    void battAvailableEnergyChanged(qreal battAvailableEnergy);
    void battMaxChgCurrentChanged(qreal battMaxChgCurrent);
    void battMaxDsgCurrentChanged(qreal battMaxDsgCurrent);
    void battResVoltageChanged(qreal battResVoltage);
    void battSungrowStatusChanged(quint8 battSungrowStatus);
    void battExceptionLChanged(quint16 battExceptionL);
    void battExceptionMChanged(quint16 battExceptionM);

    // Settings Master
    void psCellsInSeriesModChanged(quint8 psCellsInSeriesMod);
    void psCellsInSeriesBattChanged(quint16 psCellsInSeriesBatt);
    void psModulesInSeriesChanged(quint8 psModulesInSeries);
    void psOverVoltageDetThresholdChanged(quint16 psOverVoltageDetThreshold);
    void psUnderVoltageDetThresholdChanged(quint16 psUnderVoltageDetThreshold);
    void psSlOverVoltageDetThresholdChanged(quint16 psSlOverVoltageDetThreshold);
    void psSlUnderVoltageDetThresholdChanged(quint16 psSlUnderVoltageDetThreshold);
    void psDsgOcDetThresholdChanged(quint16 psDsgOcDetThreshold);
    void psChgOcDetThresholdChanged(quint16 psChgOcDetThreshold);
    void psOperatingModeChanged(quint8 psOperatingMode);
    void psMasterSlaveCommModeChanged(quint8 psMasterSlaveCommMode);
    void psDpDsgSwitchTypeChanged(quint8 psDpDsgSwitchType);
    void psDpChgSwitchTypeChanged(quint8 psDpChgSwitchType);
    void psSpSwitchTypeChanged(quint8 psSpSwitchType);
    void psSpSwitchMonitorTypeChanged(quint8 psSpSwitchMonitorType);
    void psPreDsgSwitchTypeChanged(quint8 psPreDsgSwitchType);
    void psPreDsgSwitchDurationChanged(quint8 psPreDsgSwitchDuration);
    void psIgnitionTypeChanged(quint8 psIgnitionType); 
    void psChgDetectionTypeChanged(quint8 psChgDetectionType);
    void psChgIntDetectionHighThresholdChanged(quint8 psChgIntDetectionHighThreshold);
    void psChgIntDetectionLowThresholdChanged(quint8 psChgIntDetectionLowThreshold);
    void psDsgDetectionTypeChanged(quint8 psDsgDetectionType);
    void psDsgIntDetectionThresholdChanged(quint8 psDsgIntDetectionThreshold);
    void psChargerTypeChanged(quint8 psChargerType);
    void psEarlyBalancingThsChanged(quint16 psEarlyBalancingThs);
    void psCellsAllowedDisbalanceChanged(quint16 psCellsAllowedDisbalance);
    void psChgCompleteCurrentChanged(quint16 psChgCompleteCurrent);
    void psDsgCompleteCurrentChanged(quint16 psDsgCompleteCurrent);
    void psChgConnectionTmoChanged(quint8 psChgConnectionTmo);
    void psDsgConnectionTmoChanged(quint8 psDsgConnectionTmo);
    void psBatteryCapacityChanged(quint32 psBatteryCapacity);
    void psStateOfChargeChanged(quint16 psStateOfCharge);
    void psFullyChgVoltageDetThsChanged(quint16 psFullyChgVoltageDetThs);
    void psFullyChgVoltageRecThsChanged(quint16 psFullyChgVoltageRecThs);
    void psFullyChgVoltageToleranceChanged(quint16 psFullyChgVoltageTolerance);
    void psFullyChgSwitchCtrlDisableChanged(quint8 psFullyChgSwitchCtrlDisable);
    void psAiInHighThresholdChanged(quint16 psAiInHighThreshold);
    void psAiInLowThresholdChanged(quint16 psAiInLowThreshold);
    void psExtOutputOCTmoChanged(quint16 psExtOutputOCTmo);
    void psExtOutputOCRecTmoChanged(quint16 psExtOutputOCRecTmo);
    void psExtNtcSensorTypeChanged(quint8 psExtNtcSensorType);
    void psExtNtcSensorEnStatusChanged(quint8 psExtNtcSensorEnStatus);
    void psExtCurrentSensorTypeChanged(quint8 psExtCurrentSensorType);
    void psExtCurrentSensorInvertChanged(quint8 psExtCurrentSensorInvert);
    void psCurrentAvgLevelChanged(quint8 psCurrentAvgLevel);
    void psSwDiagnosticsDisableChanged(quint8 psSwDiagnosticsDisable);
    void pseFullyDsgSwitchCtrlDisableChanged(quint8 pseFullyDsgSwitchCtrlDisable);
    void pseOverVoltageDetThsChanged(quint16 pseOverVoltageDetThs);
    void pseOverVoltageRecThsChanged(quint16 pseOverVoltageRecThs);
    void pseFullyDsgVoltageDetThsChanged(quint16 pseFullyDsgVoltageDetThs);
    void pseFullyDsgVoltageRecThsChanged(quint16 pseFullyDsgVoltageRecThs);
    void pseUnderVoltageDetThsChanged(quint16 pseUnderVoltageDetThs);
    void pseUnderVoltageRecThsChanged(quint16 pseUnderVoltageRecThs);
    void pseDsgOverCurrentDetThs1Changed(quint16 pseDsgOverCurrentDetThs1);
    void pseDsgOverCurrentDetThs2Changed(quint16 pseDsgOverCurrentDetThs2);
    void pseDsgOverCurrentDetTmo1Changed(quint16 pseDsgOverCurrentDetTmo1);
    void pseDsgOverCurrentDetTmo2Changed(quint16 pseDsgOverCurrentDetTmo2);
    void pseRegOverCurrentDetThs1Changed(quint16 pseRegOverCurrentDetThs1);
    void pseRegOverCurrentDetThs2Changed(quint16 pseRegOverCurrentDetThs2);
    void pseRegOverCurrentDetTmo1Changed(quint16 pseRegOverCurrentDetTmo1);
    void pseRegOverCurrentDetTmo2Changed(quint16 pseRegOverCurrentDetTmo2);
    void pseChgOverCurrentDetThs1Changed(quint16 pseChgOverCurrentDetThs1);
    void pseChgOverCurrentDetThs2Changed(quint16 pseChgOverCurrentDetThs2);
    void pseChgOverCurrentDetTmo1Changed(quint16 pseChgOverCurrentDetTmo1);
    void pseChgOverCurrentDetTmo2Changed(quint16 pseChgOverCurrentDetTmo2);
    void pseCellOverTempDetThsChanged(qint16 pseCellOverTempDetThs);
    void pseCellOverTempRecThsChanged(qint16 pseCellOverTempRecThs);
    void pseCellChgUnderTempDetThsChanged(qint16 pseCellChgUnderTempDetThs);
    void pseCellChgUnderTempRecThsChanged(qint16 pseCellChgUnderTempRecThs);
    void pseCellUnderTempDetThsChanged(qint16 pseCellUnderTempDetThs);
    void pseCellUnderTempRecThsChanged(qint16 pseCellUnderTempRecThs);
    void pseCellDiscDetThsChanged(quint16 pseCellDiscDetThs);
    void pseCellDiscDetTmoChanged(quint8 pseCellDiscDetTmo);
    void pseCellConnDetThsChanged(quint16 pseCellConnDetThs);
    void pseCellConnDetTmoChanged(quint8 pseCellConnDetTmo);
    void pseExceptionRecTmoChanged(quint16 pseExceptionRecTmo);
    void pseChgEventsDisableChanged(quint8 pseChgEventsDisable);
    void pseStateOfHealthChanged(quint16 pseStateOfHealth);
    void pseShBattNominalEnergyChanged(quint32 pseShBattNominalEnergy);
    void pseShBattSerialModulesChanged(quint8 pseShBattSerialModules);
    void pseEnMaxCurrentCtrlChanged(quint8 pseEnMaxCurrentCtrl);
    void pseMasterCellVCheckDisableChanged(quint8 pseMasterCellVCheckDisable);
    void pseMasterCellTCheckDisableChanged(quint8 pseMasterCellTCheckDisable);
    void pseCellResistanceChanged(quint16 pseCellResistance);
    void pseExtModuleTypeChanged(quint8 pseExtModuleType);
    void pseEcsLowChSensChanged(quint16 pseEcsLowChSens);
    void pseEcsHighChSensChanged(quint16 pseEcsHighChSens);
    void pseContinuousBalEnableChanged(quint8 pseContinuousBalEnable);
    void pseIcsSensChanged(quint16 pseIcsSens);

private:
    // Live Data Master
    QVector<qreal> *pMasterCellVolt;
    QVector<qreal> *pMasterCellTemp;
    QVector<qreal> *pMasterBmsTemp;
    qreal pMasterMinCellVoltage;
    qreal pMasterMaxCellVoltage;
    qreal pMasterMinCellTemp;
    qreal pMasterMaxCellTemp;
    qreal pMasterMinBmsTemp;
    qreal pMasterMaxBmsTemp;
    qreal pMasterModuleVoltage;
    quint16 pMasterBmsState;
    quint16 pMasterBalancingBits;
    quint16 pMasterBalancingDuration;
    quint32 pMasterLifeTimeCounter;
    quint16 pMasterPeriphStatus;

    // Live Data Battery
    qreal pBattVoltage;
    qreal pBattMinCellVoltage;
    qreal pBattMaxCellVoltage;
    qreal pBattMinCellTemp;
    qreal pBattMaxCellTemp;
    qreal pBattMinBmsTemp;
    qreal pBattMaxBmsTemp;
    qreal pBattIntCurrent;
    qreal pBattIntCurrentAvg;
    qreal pBattExtCurrent;
    qreal pBattExtCurrentAvg;
    qreal pBattCurrent;
    qreal pBattCurrentAvg;
    qreal pBattStateOfCharge;
    qreal pBattStateOfHealth;
    qreal pBattAvailableEnergy;
    qreal pBattMaxChgCurrent;
    qreal pBattMaxDsgCurrent;
    qreal pBattResVoltage;
    quint8 pBattSungrowStatus;
    quint16 pBattExceptionL;
    quint16 pBattExceptionM;

    // Settings Master
    quint8 psetCellsInSeriesMod;
    quint16 psetCellsInSeriesBatt;
    quint8 psetModulesInSeries;
    quint16 psetOverVoltageDetThreshold;
    quint16 psetUnderVoltageDetThreshold;
    quint16 psetSlOverVoltageDetThreshold;
    quint16 psetSlUnderVoltageDetThreshold;
    quint16 psetDsgOcDetThreshold;
    quint16 psetChgOcDetThreshold;
    quint8 psetOperatingMode;
    quint8 psetMasterSlaveCommMode;
    quint8 psetDpDsgSwitchType;
    quint8 psetDpChgSwitchType;
    quint8 psetSpSwitchType;
    quint8 psetSpSwitchMonitorType;
    quint8 psetPreDsgSwitchType;
    quint8 psetPreDsgSwitchDuration;
    quint8 psetIgnitionType;
    quint8 psetChgDetectionType;
    quint8 psetChgIntDetectionHighThreshold;
    quint8 psetChgIntDetectionLowThreshold;
    quint8 psetDsgDetectionType;
    quint8 psetDsgIntDetectionThreshold;
    quint8 psetChargerType;
    quint16 psetEarlyBalancingThs;
    quint16 psetCellsAllowedDisbalance;
    quint16 psetChgCompleteCurrent;
    quint16 psetDsgCompleteCurrent;
    quint8 psetChgConnectionTmo;
    quint8 psetDsgConnectionTmo;
    quint32 psetBatteryCapacity;
    quint16 psetStateOfCharge;
    quint16 psetFullyChgVoltageDetThs;
    quint16 psetFullyChgVoltageRecThs;
    quint16 psetFullyChgVoltageTolerance;
    quint8 psetFullyChgSwitchCtrlDisable;
    quint16 psetAiInHighThreshold;
    quint16 psetAiInLowThreshold;
    quint16 psetExtOutputOCTmo;
    quint16 psetExtOutputOCRecTmo;
    quint8 psetExtNtcSensorType;
    quint8 psetExtNtcSensorEnStatus;
    quint8 psetExtCurrentSensorType;
    quint8 psetExtCurrentSensorInvert;
    quint8 psetCurrentAvgLevel;
    quint8 psetSwDiagnosticsDisable;
    quint8 epsetFullyDsgSwitchCtrlDisable;
    quint16 epsetOverVoltageDetThs;
    quint16 epsetOverVoltageRecThs;
    quint16 epsetFullyDsgVoltageDetThs;
    quint16 epsetFullyDsgVoltageRecThs;
    quint16 epsetUnderVoltageDetThs;
    quint16 epsetUnderVoltageRecThs;
    quint16 epsetDsgOverCurrentDetThs1;
    quint16 epsetDsgOverCurrentDetThs2;
    quint16 epsetDsgOverCurrentDetTmo1;
    quint16 epsetDsgOverCurrentDetTmo2;
    quint16 epsetRegOverCurrentDetThs1;
    quint16 epsetRegOverCurrentDetThs2;
    quint16 epsetRegOverCurrentDetTmo1;
    quint16 epsetRegOverCurrentDetTmo2;
    quint16 epsetChgOverCurrentDetThs1;
    quint16 epsetChgOverCurrentDetThs2;
    quint16 epsetChgOverCurrentDetTmo1;
    quint16 epsetChgOverCurrentDetTmo2;
    qint16 epsetCellOverTempDetThs;
    qint16 epsetCellOverTempRecThs;
    qint16 epsetCellChgUnderTempDetThs;
    qint16 epsetCellChgUnderTempRecThs;
    qint16 epsetCellUnderTempDetThs;
    qint16 epsetCellUnderTempRecThs;
    quint16 epsetCellDiscDetThs;
    quint8 epsetCellDiscDetTmo;
    quint16 epsetCellConnDetThs;
    quint8 epsetCellConnDetTmo;
    quint16 epsetExceptionRecTmo;
    quint8 epsetChgEventsDisable;
    quint16 epsetStateOfHealth;
    quint16 epsetShBattNominalEnergy;
    quint8 epsetShBattSerialModules;
    quint8 epsetEnMaxCurrentCtrl;
    quint8 epsetMasterCellVCheckDisable;
    quint8 epsetMasterCellTCheckDisable;
    quint16 epsetCellResistance;
    quint8 epsetExtModuleType;
    quint16 epsetEcsLowChSens;
    quint16 epsetEcsHighChSens;
    quint8 epsetContinuousBalEnable;
    quint16 epsetIcsSens;
};

#endif // DATAPROFILE_H
