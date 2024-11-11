import QtQuick 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.14

Item{
    antialiasing: true

    function getBDataEnableStatus() {
        return ((sPort.connBMSFlag) && (sPort.dataReadyFlag) && (!sPort.fwActiveFlag) && (!sPort.fwSlaveActiveFlag))? true:false
    }

    function getBmsStateString(bmsState) {
        var bmsStateStr;

        switch(bmsState)
        {
        case 0: bmsStateStr = qsTr("-"); break;
        case 1: bmsStateStr = qsTr("INITIALIZATION"); break;
        case 2: bmsStateStr = qsTr("IDLE"); break;
        case 3: bmsStateStr = qsTr("DISCHARGING"); break;
        case 4: bmsStateStr = qsTr("CHARGING"); break;
        case 5: bmsStateStr = qsTr("REGENERATION"); break;
        case 6: bmsStateStr = qsTr("EXCEPTION"); break;
        case 7: bmsStateStr = qsTr("EXCEPTION (DISCHARGING)"); break;
        case 8: bmsStateStr = qsTr("EXCEPTION (CHARGING)"); break;
        case 9: bmsStateStr = qsTr("EXCEPTION (REGENERATION)"); break;
        case 10: bmsStateStr = qsTr("CHARGING COMPLETED"); break;
        case 11: bmsStateStr = qsTr("SLEEP"); break;
        default: bmsStateStr = qsTr("-"); break;
        }

        return bmsStateStr;
    }

    function getIgnitionStatusString(periphStatus) {
        var ignitionStatusStr;

        periphStatus = (periphStatus & 0x000C) >> 2;

        switch(periphStatus)
        {
        case 0: ignitionStatusStr = qsTr("DISABLED"); break;
        case 1: ignitionStatusStr = qsTr("OFF"); break;
        case 2: ignitionStatusStr = qsTr("ON"); break;
        default: ignitionStatusStr = qsTr("-"); break;
        }

        return ignitionStatusStr;
    }

    Rectangle {
        id: biItemBackgroundId
        height: parent.height
        width: parent.width
        anchors.fill: parent
        color: "#252525"
        antialiasing: true

        ColumnLayout {
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                Layout.minimumHeight: parent.height / 6
                Layout.maximumHeight: parent.height / 6
                Layout.preferredHeight: parent.height / 6

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.topMargin: biItemBackgroundId.height * 0.008
                    Layout.leftMargin: biItemBackgroundId.width * 0.008
                    Layout.rightMargin: biItemBackgroundId.width * 0.008

                    Item {
                        Layout.alignment: Qt.AlignLeft
                        antialiasing: true

                        BiLabelN {
                            id: biLabelBMSStateId
                            biName: qsTr("BMS STATE: ")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelBMSStateValueId
                            anchors.left: biLabelBMSStateId.right
                            biName: getBDataEnableStatus()? (getBmsStateString(dataProfile.masterBmsState)):qsTr("DISCONNECTED")
                            biColor: "#e9967a"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelCHGSwitchId
                            anchors.top: biLabelBMSStateId.bottom
                            biName: qsTr("CHG STATUS: ")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelCHGSwitchValueId
                            anchors.top: biLabelBMSStateId.bottom
                            anchors.left: biLabelCHGSwitchId.right
                            biName: (getBDataEnableStatus()&&(dataProfile.masterPeriphStatus&(1<<0)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus()&&(dataProfile.masterPeriphStatus&(1<<0)))? "#e9967a":"#ffffff"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelDSGSwitchId
                            anchors.top: biLabelCHGSwitchId.bottom
                            biName: qsTr("IGNITION: ")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelDSGSwitchValueId
                            anchors.top: biLabelCHGSwitchId.bottom
                            anchors.left: biLabelDSGSwitchId.right
                            biName: getBDataEnableStatus()? getIgnitionStatusString(dataProfile.masterPeriphStatus):qsTr("DISABLED")
                            biColor: "#e9967a"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }
                    }
                }

                BiGaugeSOC {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignCenter
                    Layout.leftMargin: biItemBackgroundId.width * 0.008
                    Layout.rightMargin: biItemBackgroundId.width * 0.008
                    Layout.topMargin: biItemBackgroundId.height * 0.11
                    Layout.bottomMargin: biItemBackgroundId.height * (-0.13)

                    width: parent.height
                    height: parent.height
                    biMinValue: 10
                    biValue: getBDataEnableStatus() ? dataProfile.battStateOfCharge : 0
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.topMargin: biItemBackgroundId.height * 0.008
                    Layout.leftMargin: biItemBackgroundId.width * 0.008
                    Layout.rightMargin: biItemBackgroundId.width * 0.008

                    Item {
                        antialiasing: true

                        BiLabelN {
                            id: biLabelCHGStateId
                            biName: qsTr("CHG: ")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelCHGStateValueId
                            anchors.left: biLabelCHGStateId.right
                            biName: (getBDataEnableStatus()&&(dataProfile.masterPeriphStatus&(1<<0)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus()&&(dataProfile.masterPeriphStatus&(1<<0)))? "#e9967a":"#ffffff"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelDSGStateId
                            anchors.top: biLabelCHGStateId.bottom
                            biName: qsTr("DSG: ")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiLabelN {
                            id: biLabelDSGStateValueId
                            anchors.left: biLabelDSGStateId.right
                            anchors.top: biLabelCHGStateValueId.bottom
                            biName: (getBDataEnableStatus()&&(dataProfile.masterPeriphStatus&(1<<1)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus()&&(dataProfile.masterPeriphStatus&(1<<1)))? "#e9967a":"#ffffff"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.03
                        }

                        BiDelayButton {
                            id: biRestartBMSDBId
                            antialiasing: true
                            anchors.left: biLabelCHGStateValueId.right
                            anchors.leftMargin: biItemBackgroundId.width * 0.055
                            biAutoReset: true
                            biText: qsTr("RESTART\nBMS")
                            biSize: biItemBackgroundId.width * 0.082

                            enabled: getBDataEnableStatus()? true:false
                            opacity: getBDataEnableStatus()? 1:0.5

                            onBiActivatedFlagChanged:{
                                if(biRestartBMSDBId.biActivatedFlag === true){ sPort.requestCmdSend(0x02, 0x04, 0x01); }
                            }
                        }

                        BiDelayButton {
                            id: biDisableLoadDBId
                            anchors.left: biRestartBMSDBId.right
                            anchors.leftMargin: biItemBackgroundId.width * 0.01
                            biDelay: 500
                            biText: qsTr("DISABLE\nLOAD")
                            biSize: biItemBackgroundId.width * 0.082

                            enabled: getBDataEnableStatus()? true:false
                            opacity: getBDataEnableStatus()? 1:0.5

                            onBiActivatedFlagChanged:{
                                if(biDisableLoadDBId.biActivatedFlag === true){ sPort.requestCmdSend(0x06, 0x00, 0x01); }
                                else{ sPort.requestCmdSend(0x06, 0x01, 0x01); }
                            }
                        }

                        BiDelayButton {
                            id: biDisableChargerDBId
                            anchors.left: biRestartBMSDBId.right
                            anchors.top: biDisableLoadDBId.bottom
                            anchors.leftMargin: biItemBackgroundId.width * 0.01
                            anchors.topMargin: biItemBackgroundId.height * 0.015
                            biDelay: 500
                            biText: qsTr("DISABLE\nCHARGER")
                            biSize: biItemBackgroundId.width * 0.082

                            enabled: getBDataEnableStatus()? true:false
                            opacity: getBDataEnableStatus()? 1:0.5

                            onBiActivatedFlagChanged:{
                                if(biDisableChargerDBId.biActivatedFlag === true){sPort.requestCmdSend(0x07, 0x00, 0x01); }
                                else{sPort.requestCmdSend(0x07, 0x01, 0x01); }
                            }
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter
                    Layout.leftMargin: parent.width * 0.01
                    antialiasing: true

                    BiGaugeBattVoltage {
                        Layout.alignment: Qt.AlignCenter
                        width: parent.width
                        height: parent.height

                        biValue: getBDataEnableStatus()? dataProfile.battVoltage:0
                        biMinValue: getBDataEnableStatus()? (dataProfile.psCellsInSeriesMod * dataProfile.psUnderVoltageDetThreshold / 1000):10
                        biMaxValue: getBDataEnableStatus()? (dataProfile.psCellsInSeriesMod * dataProfile.psOverVoltageDetThreshold / 1000):90
                        biTickStepSize: getBDataEnableStatus()? (biMaxValue/biMinValue):10
                        biStepSize: 0.1
                    }

                    BiLabelN {
                        id: biLabelBalancingNoneId
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.02
                    }

                    BiLabelN {
                        id: biLabelBalancingId
                        anchors.top: biLabelBalancingNoneId.bottom
                        biName: qsTr("BALANCING: ")
                        biColor: "#e0e0e0"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.025
                    }

                    BiLabelN {
                        id: biLabelBalancingValueId
                        anchors.top: biLabelBalancingId.bottom
                        biName: getBDataEnableStatus()? qsTr(dataProfile.masterBalancingDuration + " %"):qsTr("0 %")
                        biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingDuration > 0))? "#e9967a":"#ffffff"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.025
                    }

                    Item {
                        id: biItemC1Id
                        anchors.top: biLabelBalancingValueId.bottom
                        antialiasing: true

                        BiLabelN {
                            id: biLabelNoneId
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelNoneValueId
                            anchors.left: biLabelC1Id.right
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelStatusId
                            anchors.top: biLabelNoneId.bottom
                            biName: qsTr("STATUS:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelStatusValueId
                            anchors.top: biLabelNoneValueId.bottom
                            anchors.left: biLabelStatusId.right
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC1Id
                            anchors.top: biLabelStatusId.bottom
                            biName: qsTr("C1:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC1ValueId
                            anchors.top: biLabelStatusValueId.bottom
                            anchors.left: biLabelC1Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<0)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<0)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC2Id
                            anchors.top: biLabelC1Id.bottom
                            biName: qsTr("C2:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC2ValueId
                            anchors.top: biLabelC1ValueId.bottom
                            anchors.left: biLabelC2Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<1)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<1)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC3Id
                            anchors.top: biLabelC2Id.bottom
                            biName: qsTr("C3:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC3ValueId
                            anchors.top: biLabelC2ValueId.bottom
                            anchors.left: biLabelC3Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<2)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<2)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC4Id
                            anchors.top: biLabelC3Id.bottom
                            biName: qsTr("C4:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC4ValueId
                            anchors.top: biLabelC3ValueId.bottom
                            anchors.left: biLabelC4Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<3)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<3)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC5Id
                            anchors.top: biLabelC4Id.bottom
                            biName: qsTr("C5:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC5ValueId
                            anchors.top: biLabelC4ValueId.bottom
                            anchors.left: biLabelC5Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<4)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<4)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC6Id
                            anchors.top: biLabelC5Id.bottom
                            biName: qsTr("C6:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC6ValueId
                            anchors.top: biLabelC5ValueId.bottom
                            anchors.left: biLabelC6Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<5)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<5)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC7Id
                            anchors.top: biLabelC6Id.bottom
                            biName: qsTr("C7:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC7ValueId
                            anchors.top: biLabelC6ValueId.bottom
                            anchors.left: biLabelC7Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<6)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<6)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC8Id
                            anchors.top: biLabelC7Id.bottom
                            biName: qsTr("C8:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC8ValueId
                            anchors.top: biLabelC7ValueId.bottom
                            anchors.left: biLabelC8Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<7)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<7)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC9Id
                            anchors.top: biLabelC8Id.bottom
                            biName: qsTr("C9:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC9ValueId
                            anchors.top: biLabelC8ValueId.bottom
                            anchors.left: biLabelC9Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<8)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<8)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC10Id
                            anchors.top: biLabelC9Id.bottom
                            biName: qsTr("C10:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC10ValueId
                            anchors.top: biLabelC9ValueId.bottom
                            anchors.left: biLabelC10Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<9)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<9)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC11Id
                            anchors.top: biLabelC10Id.bottom
                            biName: qsTr("C11:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC11ValueId
                            anchors.top: biLabelC10ValueId.bottom
                            anchors.left: biLabelC11Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<10)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<10)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC12Id
                            anchors.top: biLabelC11Id.bottom
                            biName: qsTr("C12:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC12ValueId
                            anchors.top: biLabelC11ValueId.bottom
                            anchors.left: biLabelC12Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<11)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<11)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC13Id
                            anchors.top: biLabelC12Id.bottom
                            biName: qsTr("C13:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC13ValueId
                            anchors.top: biLabelC12ValueId.bottom
                            anchors.left: biLabelC13Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<12)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<12)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC14Id
                            anchors.top: biLabelC13Id.bottom
                            biName: qsTr("C14:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC14ValueId
                            anchors.top: biLabelC13ValueId.bottom
                            anchors.left: biLabelC14Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<13)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<13)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC15Id
                            anchors.top: biLabelC14Id.bottom
                            biName: qsTr("C15:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC15ValueId
                            anchors.top: biLabelC14ValueId.bottom
                            anchors.left: biLabelC15Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<14)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<14)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC16Id
                            anchors.top: biLabelC15Id.bottom
                            biName: qsTr("C16:")
                            biColor: "#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }

                        BiLabelN {
                            id: biLabelC16ValueId
                            anchors.top: biLabelC15ValueId.bottom
                            anchors.left: biLabelC16Id.right
                            biName: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<15)))? qsTr("ON"):qsTr("OFF")
                            biColor: (getBDataEnableStatus() && (dataProfile.masterBalancingBits & (1<<15)))? "#e9967a":"#e0e0e0"
                            biBackground: "#252525"
                            biTextSize: biItemBackgroundId.height * 0.02
                        }
                    }
                }

                Item {
                    Layout.alignment: Qt.AlignCenter
                    Layout.topMargin: parent.height * (-0.2)
                    antialiasing: true

                    id:biItemId

                    BiLabelN {
                        id: biLabelICSid
                        anchors.horizontalCenter: parent.horizontalCenter
                        biName: qsTr("ICS")
                        biColor: "#e0e0e0"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.025
                    }

                    BiLabelN {
                        id: biLabelICSValueid
                        anchors.top: biLabelICSid.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        biName: getBDataEnableStatus()? qsTr(dataProfile.battIntCurrentAvg.toFixed(1) + " A"):qsTr("0.0 A")
                        biColor: "#ffffff"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.03
                    }

                    BiLabelN {
                        id: biLabelEmptyId
                        anchors.top: biLabelICSValueid.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        biName: qsTr("")
                        biColor: "#e0e0e0"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.02
                    }

                    BiLabelN {
                        id: biLabelECSid
                        anchors.top: biLabelEmptyId.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        biName: qsTr("ECS")
                        biColor: "#e0e0e0"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.025
                    }

                    BiLabelN {
                        id: biLabelECSValueid
                        anchors.top: biLabelECSid.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        biName: getBDataEnableStatus()? qsTr(dataProfile.battExtCurrentAvg.toFixed(1) + " A"):qsTr("0.0 A")
                        biColor: "#ffffff"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.03
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter
                    Layout.rightMargin: parent.width * 0.01
                    antialiasing: true

                    BiGaugeBattCurrent {
                        id: biGaugeCurrentId
                        width: parent.width
                        height: parent.height

                        biMinValue: getBDataEnableStatus()? (dataProfile.psDsgOcDetThreshold * (-1)):(-150)
                        biMaxValue: getBDataEnableStatus()? (dataProfile.psChgOcDetThreshold):30
                        biTickStepSize: getBDataEnableStatus()? 10:15
                        biEnabled: true
                        biValue: getBDataEnableStatus()? dataProfile.battCurrentAvg:0
                    }

                    BiLabelN {
                        id: biLabelBMSTempId
                        anchors.bottom: biLabelBMSTempValueId.top
                        anchors.left: biGaugeCurrentId.left
                        anchors.leftMargin: parent.width * 0.05
                        biName: qsTr("BMS")
                        biColor: "#e0e0e0"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.02
                    }

                    BiLabelN {
                        id: biLabelBMSTempValueId
                        anchors.bottom: biGaugeCurrentId.bottom
                        anchors.left: biGaugeCurrentId.left
                        anchors.bottomMargin: parent.height * 0.06
                        anchors.leftMargin: parent.width * 0.05
                        biName: (getBDataEnableStatus() && (dataProfile.battMaxBmsTemp !== -32768))? qsTr((dataProfile.battMaxBmsTemp).toFixed(1) + " \xB0C"):qsTr("25.0 \xB0C")
                        biColor: (getBDataEnableStatus() && (dataProfile.battMaxBmsTemp >= 0) && (dataProfile.battMaxBmsTemp <= 90))? "#ffffff":
                                                                                                                                         (!getBDataEnableStatus())? "#ffffff":"#e9967a"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.025
                    }

                    BiLabelN {
                        id: biLabelCELLTempId
                        anchors.bottom: biLabelCELLTempValueId.top
                        anchors.right: biGaugeCurrentId.right
                        anchors.rightMargin: parent.width * 0.015
                        biName: qsTr("CELL")
                        biColor: "#e0e0e0"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.02
                    }

                    BiLabelN {
                        id: biLabelCELLTempValueId
                        anchors.bottom: biGaugeCurrentId.bottom
                        anchors.right: biGaugeCurrentId.right
                        anchors.bottomMargin: parent.height * 0.06
                        anchors.rightMargin: parent.width * 0.015
                        biName: (getBDataEnableStatus() && (dataProfile.battMaxCellTemp !== -32768))? qsTr((dataProfile.battMaxCellTemp).toFixed(1) + " \xB0C"):qsTr("25.0 \xB0C")
                        biColor: (getBDataEnableStatus() && (dataProfile.battMaxCellTemp >= 0) && (dataProfile.battMaxCellTemp <= 90))? "#ffffff":
                                                                                                                                         (!getBDataEnableStatus())? "#ffffff":"#e9967a"
                        biBackground: "#252525"
                        biTextSize: biItemBackgroundId.height * 0.025
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                Layout.leftMargin: parent.width * 0.01
                Layout.minimumHeight: parent.height / 4
                Layout.maximumHeight: parent.height / 4
                Layout.preferredHeight: parent.height / 4

                BiGaugeCellVoltage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter
                    Layout.topMargin: biItemBackgroundId.height * 0.07
                    Layout.bottomMargin: biItemBackgroundId.height * (-0.01)
                    biCellName: qsTr("MIN")
                    width: parent.width
                    height: parent.height

                    biMinValueF: getBDataEnableStatus()? (dataProfile.psUnderVoltageDetThreshold / 1000):2.5
                    biMaxValueF: getBDataEnableStatus()? (dataProfile.psOverVoltageDetThreshold / 1000):4.2
                    biValueF: getBDataEnableStatus()? (dataProfile.masterMinCellVoltage):0
                }

                BiGaugeCellVoltage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter
                    Layout.topMargin: biItemBackgroundId.height * 0.07
                    Layout.bottomMargin: biItemBackgroundId.height * (-0.01)
                    biCellName: qsTr("MAX")
                    width: parent.width
                    height: parent.height

                    biMinValueF: getBDataEnableStatus()? (dataProfile.psUnderVoltageDetThreshold / 1000):2.5
                    biMaxValueF: getBDataEnableStatus()? (dataProfile.psOverVoltageDetThreshold / 1000):4.2
                    biValueF: getBDataEnableStatus()? (dataProfile.masterMaxCellVoltage):0
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.leftMargin: parent.width * 0.01
                    Layout.rightMargin: parent.width * 0.003
                    Layout.alignment: Qt.AlignLeft
                    Layout.minimumWidth: parent.width / 2 - parent.width * 0.02
                    Layout.maximumWidth: parent.width / 2 - parent.width * 0.02
                    Layout.preferredWidth: parent.width / 2 - parent.width * 0.02

                    BiGauge {
                        id: biInternalTemp1Id
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        Layout.topMargin: biItemBackgroundId.height * (-0.025)
                        biHeight: parent.height + biItemBackgroundId.height * 0.01
                        biWidth: parent.width * 0.05
                        biUnit: qsTr("\xB0C")
                        biValue: (getBDataEnableStatus() && (dataProfile.masterBmsTemp[0] !== -32768))? (dataProfile.masterBmsTemp[0]):25
                    }

                    BiGauge {
                        id: biInternalTemp2Id
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        Layout.topMargin: biItemBackgroundId.height * (-0.025)
                        biHeight: parent.height + biItemBackgroundId.height * 0.01
                        biWidth: parent.width * 0.05
                        biUnit: qsTr("\xB0C")
                        biValue: (getBDataEnableStatus() && (dataProfile.masterBmsTemp[1] !== -32768))? (dataProfile.masterBmsTemp[1]):25
                    }

                    BiGauge {
                        id: biInternalTemp3Id
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        Layout.topMargin: biItemBackgroundId.height * (-0.025)
                        biHeight: parent.height + biItemBackgroundId.height * 0.01
                        biWidth: parent.width * 0.05
                        biUnit: qsTr("\xB0C")
                        biValue: (getBDataEnableStatus() && (dataProfile.masterBmsTemp[2] !== -32768))? (dataProfile.masterBmsTemp[2]):25
                    }

                    BiGauge {
                        id: biExternalTemp1Id
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        Layout.topMargin: biItemBackgroundId.height * (-0.025)
                        biHeight: parent.height + biItemBackgroundId.height * 0.01
                        biWidth: parent.width * 0.05
                        biUnit: qsTr("\xB0C")
                        biValue: (getBDataEnableStatus() && (dataProfile.masterCellTemp[0] !== -32768))? (dataProfile.masterCellTemp[0]):25
                    }

                    BiGauge {
                        id: biExternalTemp2Id
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        Layout.topMargin: biItemBackgroundId.height * (-0.025)
                        biHeight: parent.height + biItemBackgroundId.height * 0.01
                        biWidth: parent.width * 0.05
                        biUnit: qsTr("\xB0C")
                        biValue: (getBDataEnableStatus() && (dataProfile.masterCellTemp[1] !== -32768))? (dataProfile.masterCellTemp[1]):25
                    }

                    BiGauge {
                        id: biExternalTemp3Id
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        Layout.topMargin: biItemBackgroundId.height * (-0.025)
                        biHeight: parent.height + biItemBackgroundId.height * 0.01
                        biWidth: parent.width * 0.05
                        biUnit: qsTr("\xB0C")
                        biValue: (getBDataEnableStatus() && (dataProfile.masterCellTemp[2] !== -32768))? (dataProfile.masterCellTemp[2]):25
                    }

                    BiGauge {
                        id: biExternalTemp4Id
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        Layout.topMargin: biItemBackgroundId.height * (-0.025)
                        biHeight: parent.height + biItemBackgroundId.height * 0.01
                        biWidth: parent.width * 0.05
                        biUnit: qsTr("\xB0C")
                        biValue: (getBDataEnableStatus() && (dataProfile.masterCellTemp[3] !== -32768))? (dataProfile.masterCellTemp[3]):25
                    }
                }
            }
        }
    }
}
