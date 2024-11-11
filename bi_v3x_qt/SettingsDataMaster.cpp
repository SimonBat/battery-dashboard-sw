#include "SettingsDataMaster.h"

SettingsDataMaster::SettingsDataMaster(QObject *parent) : QObject(parent),
    cellsInSeriesMod(16),
    overVoltageDetThreshold(420),
    underVoltageDetThreshold(200),
    dsgOverCurrentDetThreshold_1(150),
    dsgOverCurrentDetThreshold_2(150),
    chgOverCurrentDetThreshold_1(150),
    chgOverCurrentDetThreshold_2(150),
    continuousBalancingEnable(0),
    stateOfHealth(100),
    sh10rtBattNominalEnergy(9600),
    sh10rtBattSerialModules(3),
    enMaxCurrentCtrl(0),
    masterCellVoltCheckDisable(0),
    masterCellTempCheckDisable(0),
    cellResistance(0),
    extModuleType(0),
    ecsLowChSensitivity(0),
    ecsHighChSensitivity(0),
    icsSensitivity(0)
{

}
