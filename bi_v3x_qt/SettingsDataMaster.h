#ifndef SETTINGSDATAMASTER_H
#define SETTINGSDATAMASTER_H

#include <QObject>

class SettingsDataMaster : public QObject
{
    Q_OBJECT
public:
    explicit SettingsDataMaster(QObject *parent = nullptr);

    quint8 cellsInSeriesMod;                // [Register 0 LSB]
    quint8 modulesInSeries;                 // [Register 0 MSB]
    quint16 cellsInSeriesBatt;              // [Register 1]
    quint16 overVoltageDetThreshold;        // [Register 2] Resolution 0.01V
    quint16 overVoltageRecThreshold;        // [Register 3] Resolution 0.01V
    quint16 fullyChgVoltageDetThreshold; 	// [Register 4] Resolution 0.01V
    quint16 fullyChgVoltageRecThreshold; 	// [Register 5] Resolution 0.01V
    quint16 fullyChgVoltageTolerance;       // [Register 6] Resolution 1 mV
    quint8 fullyChgSwitchCtrlDisable;       // [Register 7 LSB]
    quint8 fullyDsgSwitchCtrlDisable;       // [Register 7 MSB]
    quint16 fullyDsgVoltageDetThreshold; 	// [Register 8] Resolution 0.01V
    quint16 fullyDsgVoltageRecThreshold; 	// [Register 9] Resolution 0.01V
    quint16 underVoltageDetThreshold;       // [Register 10] Resolution 0.01V
    quint16 underVoltageRecThreshold;       // [Register 11] Resolution 0.01V
    quint16 dsgOverCurrentDetThreshold_1; 	// [Register 12] Resolution 1A
    quint16 dsgOverCurrentDetThreshold_2; 	// [Register 13] Resolution 1A
    quint8 dsgOverCurrentDetTmo_1;          // [Register 14 LSB] Resolution 1sec.
    quint8 dsgOverCurrentDetTmo_2;          // [Register 14 MSB] Resolution 1sec.
    quint16 regOverCurrentDetThreshold_1; 	// [Register 15] Resolution 1A
    quint16 regOverCurrentDetThreshold_2; 	// [Register 16] Resolution 1A
    quint8 regOverCurrentDetTmo_1;          // [Register 17 LSB] Resolution 1sec.
    quint8 regOverCurrentDetTmo_2;          // [Register 17 MSB] Resolution 1sec.
    quint16 chgOverCurrentDetThreshold_1; 	// [Register 18] Resolution 1A
    quint16 chgOverCurrentDetThreshold_2; 	// [Register 19] Resolution 1A
    quint8 chgOverCurrentDetTmo_1;          // [Register 20 LSB] Resolution 1sec.
    quint8 chgOverCurrentDetTmo_2;          // [Register 20 MSB] Resolution 1sec.
    qint16 cellOverTempDetThreshold;        // [Register 21] Resolution 1C
    qint16 cellOverTempRecThreshold;        // [Register 22] Resolution 1C
    qint16 cellChgUnderTempDetThreshold; 	// [Register 23] Resolution 1C
    qint16 cellChgUnderTempRecThreshold; 	// [Register 24] Resolution 1C
    qint16 cellUnderTempDetThreshold;       // [Register 25] Resolution 1C
    qint16 cellUnderTempRecThreshold;       // [Register 26] Resolution 1C
    quint16 cellDiscDetThreshold;           // [Register 27] Resolution 0.01V
    quint8 cellDiscDetTmo;                  // [Register 28 LSB] Resolution 1sec.
    quint8 reserved_1;                      // [Register 28 MSB]
    quint16 cellConnDetThreshold;           // [Register 29] Resolution 0.01V
    quint8 cellConnDetTmo;                  // [Register 30 LSB] Resolution 1sec.
    quint8 reserved_2;                      // [Register 30 MSB]
    quint16 exceptionRecoveryTmo;           // [Register 31] Resolution 1sec.
    quint16 aiInHighThreshold;              // [Register 32] Resolution 0.1V
    quint16 aiInLowThreshold;               // [Register 33] Resolution 0.1V
    quint16 reserved_3;                     // [Register 34]
    quint16 reserved_4;                     // [Register 35]
    quint16 extOutputOCTmo;                 // [Register 36] Resolution 10ms
    quint16 extOutputOCRecoveryTmo;         // [Register 37] Resolution 1sec.
    quint8 extNtcSensorType;                // [Register 38 LSB]
    quint8 extNtcSensorEnStatus;            // [Register 38 MSB]
    quint8 extCurrentSensorType;            // [Register 39 LSB]
    quint8 extCurrentSensorInvert;          // [Register 39 MSB]
    quint8 currentAvgLevel;                 // [Register 40 LSB]
    quint8 switchDiagnosticsDisable;        // [Register 40 MSB]
    quint8 operatingMode;                   // [Register 41 LSB]
    quint8 masterSlaveCommMode;             // [Register 41 MSB]
    quint8 dpDsgSwitchType;                 // [Register 42 LSB]
    quint8 dpChgSwitchType;                 // [Register 42 MSB]
    quint8 spSwitchType;                    // [Register 43 LSB]
    quint8 spSwitchMonitorType;             // [Register 43 MSB]
    quint8 preDsgSwitchType;                // [Register 44 LSB]
    quint8 preDsgSwitchDuration;            // [Register 44 MSB] Resolution 0.1sec.
    quint8 ignitionType;                    // [Register 45 LSB]
    quint8 reserved_5;                      // [Register 45 MSB]
    quint8 chgDetectionType;                // [Register 46 LSB]
    quint8 chgEventsDisable;                // [Register 46 MSB]
    quint8 chgIntDetectionHighThreshold; 	// [Register 47 LSB] Resolution 0.1V
    quint8 chgIntDetectionLowThreshold; 	// [Register 47 MSB] Resolution 0.1V
    quint8 dsgDetectionType;                // [Register 48 LSB]
    quint8 dsgIntDetectionThreshold;        // [Register 48 MSB] Resolution 0.01V
    quint8 chargerType;                     // [Register 49 LSB]
    quint8 continuousBalancingEnable;       // [Register 49 MSB]
    quint16 earlyBalancingThreshold;        // [Register 50] Resolution 0.01V
    quint16 cellsAllowedDisbalance;         // [Register 51] Resolution 1mV
    quint16 chgCompleteCurrent;             // [Register 52] Resolution 0.1A
    quint8 chargerConnectionTmo;            // [Register 53 LSB] Resolution 1sec.
    quint8 loadConnectionTmo;               // [Register 53 MSB] Resolution 1sec.
    quint32 batteryCapacity;                // [Registers 54-55] Resolution 0.01Ah
    quint16 stateOfCharge;                  // [Register 56] Resolution 1%
    quint16 stateOfHealth;                  // [Register 57] Resolution 1%
    quint32 sh10rtBattNominalEnergy;        // [Registers 58-59] Resolution 1kWh
    quint8 sh10rtBattSerialModules;         // [Register 60 LSB]
    quint8 enMaxCurrentCtrl;                // [Register 60 MSB]
    quint8 masterCellVoltCheckDisable;      // [Register 61 MSB]
    quint8 masterCellTempCheckDisable;      // [Register 61 LSB]
    quint16 cellResistance;                 // [Register 62] Resolution 1mOhm
    quint8 extModuleType;                   // [Register 63 LSB]
    quint8 reserved_6;                      // [Register 63 MSB]
    quint16 ecsLowChSensitivity;            // [Register 64] uV/A
    quint16 ecsHighChSensitivity;			// [Register 65] uV/A
    quint16 icsSensitivity;                 // [Register 66] uV/A
    quint16 dsgCompleteCurrent;             // [Register 67] Resolution 0.1A
signals:

};

#endif // SETTINGSDATAMASTER_H
