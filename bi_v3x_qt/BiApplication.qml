import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.12

Item {
    property string serialPortStatus: biCBPortsListId.currentText
    property bool autoScanFlag: biRBSerialPortAutomaticId.checked? true:false
    antialiasing: true

    Component.onCompleted: { sPort.scanSerialPorts(); }

    id: biApplicationWindowId
    visible: true
    width: 800
    height: 558

    Timer {
        interval: 500
        running: true
        repeat: false
        onTriggered:
        {
            if(biRBSerialPortAutomaticId.checked) { sPort.startAutoConnectionScan(); }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#aaaaaa"
    }

    Material.theme: Material.Light
    Material.accent: "#184180"
    Material.background: "#aaaaaa"
    FontLoader { id: localFontId; source: "tahoma.ttf" }

    ColumnLayout {
        anchors.fill: parent
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: biApplicationWindowId.height * 0.001

        Item {
            id: biHeaderId

            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.minimumHeight: biApplicationWindowId.height * 0.042
            Layout.maximumHeight: biApplicationWindowId.height * 0.042
            Layout.preferredHeight: biApplicationWindowId.height * 0.042

            Rectangle {
                id: biHeaderRecId
                anchors.fill: parent
                color: "#252525"

                RowLayout {
                    id: biHeaderRecRowId
                    anchors.fill: parent

                    Label {
                        id: biHeaderLPortId
                        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                        Layout.leftMargin: biApplicationWindowId.width * 0.012

                        height: font.pixelSize
                        text: qsTr("Serial Port Connection Mode: ")
                        font.pixelSize: biApplicationWindowId.height * 0.02
                        color: "#ffffff"
                        renderType: Text.QtRendering;
                        font.capitalization: Font.MixedCase
                        font.hintingPreference: Font.PreferFullHinting
                        font.bold: false
                        font.family: localFontId.name
                        font.italic: false
                        font.weight: Font.Thin
                        font.kerning: true
                        font.overline: false
                        font.preferShaping: true
                    }

                    BiRadioButton{
                        id: biRBSerialPortAutomaticId
                        checked: true
                        biText: qsTr("AUTOMATIC")
                        biSize: biApplicationWindowId.height * 0.026

                        onCheckedChanged: {
                            if(checked)
                            {
                                sPort.closeSerialPort();
                                sPort.scanSerialPorts();
                                sPort.startAutoConnectionScan();
                            }
                        }
                    }

                    BiRadioButton {
                        id: biRBSerialPortManualId
                        biText: qsTr("MANUAL")
                        biSize: biApplicationWindowId.height * 0.026

                        onCheckedChanged: {
                            if(checked) { sPort.stopAutoConnectionScan(); }
                        }
                    }

                    // Separator
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.preferredWidth: biApplicationWindowId.width * 0.0012
                        Layout.minimumWidth: biApplicationWindowId.width * 0.0012
                        Layout.maximumWidth: biApplicationWindowId.width * 0.0012
                        Layout.topMargin: biApplicationWindowId.height * 0.0055
                        Layout.leftMargin: biApplicationWindowId.width * 0.0125
                        Layout.minimumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.maximumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.preferredHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        color: "#aaaaaa"
                    }

                    BiButton {
                        Layout.alignment: Qt.AlignTop
                        Layout.leftMargin: biApplicationWindowId.width * 0.0125
                        Layout.topMargin: biApplicationWindowId.height * 0.005
                        biText: qsTr("SCAN PORTS")
                        biWidth: biApplicationWindowId.height * 0.164
                        biHeight: biApplicationWindowId.height * 0.03

                        enabled: ((biRBSerialPortManualId.checked) && (sPort.openPortFlag === false))
                        opacity: ((biRBSerialPortManualId.checked) && (sPort.openPortFlag === false))? 1:0.5

                        onClicked: {
                            sPort.scanSerialPorts();
                        }
                    }

                    BiComboBox {
                        id: biCBPortsListId
                        Layout.leftMargin: biApplicationWindowId.width * 0.0125
                        biWidth: biApplicationWindowId.height * 0.164
                        biHeight: biApplicationWindowId.height * 0.03
                        model: sPort.portsList

                        enabled: ((biRBSerialPortManualId.checked) && (sPort.portsNumber > 0) && (sPort.openPortFlag === false))
                        opacity: ((biRBSerialPortManualId.checked) && (sPort.portsNumber > 0) && (sPort.openPortFlag === false))? 1:0.5
                    }

                    // Separator
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.preferredWidth: biApplicationWindowId.width * 0.0012
                        Layout.minimumWidth: biApplicationWindowId.width * 0.0012
                        Layout.maximumWidth: biApplicationWindowId.width * 0.0012
                        Layout.topMargin: biApplicationWindowId.height * 0.0055
                        Layout.leftMargin: biApplicationWindowId.width * 0.0125
                        Layout.minimumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.maximumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.preferredHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        color: "#aaaaaa"
                    }

                    BiButton {
                        id: biBTOpenPortId
                        Layout.alignment: Qt.AlignTop
                        Layout.leftMargin: biApplicationWindowId.width * 0.0125
                        Layout.topMargin: biApplicationWindowId.height * 0.005
                        biText: qsTr("OPEN PORT")
                        biWidth: biApplicationWindowId.height * 0.164
                        biHeight: biApplicationWindowId.height * 0.03

                        enabled: ((biRBSerialPortManualId.checked) && (sPort.portsNumber > 0) && (sPort.openPortFlag === false))
                        opacity: ((biRBSerialPortManualId.checked) && (sPort.portsNumber > 0) && (sPort.openPortFlag === false))? 1:0.5

                        onClicked: {
                            sPort.openSerialPort(biCBPortsListId.currentText, false);
                        }
                    }

                    BiButton {
                        id: biBTClosePortId
                        Layout.alignment: Qt.AlignTop
                        Layout.leftMargin: biApplicationWindowId.width * 0.0125
                        Layout.topMargin: biApplicationWindowId.height * 0.005
                        biText: qsTr("CLOSE PORT")
                        biWidth: biApplicationWindowId.height * 0.164
                        biHeight: biApplicationWindowId.height * 0.03

                        enabled: ((biRBSerialPortManualId.checked) && (sPort.portsNumber > 0) && (sPort.openPortFlag === true))
                        opacity: ((biRBSerialPortManualId.checked) && (sPort.portsNumber > 0) && (sPort.openPortFlag === true))? 1:0.5

                        onClicked: {
                            sPort.closeSerialPort();
                        }
                    }

                    Item { Layout.fillWidth: true }
                }
            }
        }

        SwipeView {
            id: biSwipeViewId
            Layout.alignment: Qt.AlignBottom
            Layout.fillWidth: true
            Layout.fillHeight: true

            BiDashboard { id: tab_Dashboard }
        }

        Item {
            id: biFooterId
            Layout.alignment: Qt.AlignBottom
            Layout.fillWidth: true
            Layout.minimumHeight: biApplicationWindowId.height * 0.04
            Layout.maximumHeight: biApplicationWindowId.height * 0.04
            Layout.preferredHeight: biApplicationWindowId.height * 0.04

            Rectangle {
                anchors.fill: parent
                color: "#252525"

                RowLayout {
                    anchors.fill: parent

                    Label {
                        id: biFooterLPortId
                        Layout.alignment: (Qt.AlignLeft | Qt.AlignVCenter)
                        Layout.fillWidth: true
                        Layout.maximumWidth: biApplicationWindowId.width * 0.18
                        Layout.leftMargin: biApplicationWindowId.width * 0.012
                        Layout.topMargin: biApplicationWindowId.height * (-0.003)

                        width: Layout.maximumWidth
                        height: font.pixelSize
                        text: autoScanFlag? qsTr("Serial Port: " + sPort.openPortName):qsTr("Serial Port: " + serialPortStatus)
                        font.pixelSize: biApplicationWindowId.height * 0.02
                        color: "#ffffff"
                        renderType: Text.QtRendering;
                        font.capitalization: Font.MixedCase
                        font.hintingPreference: Font.PreferFullHinting
                        font.bold: false
                        font.family: localFontId.name
                        font.italic: false
                        font.weight: Font.Thin
                        font.kerning: true
                        font.letterSpacing: 0
                        font.overline: false
                        font.preferShaping: true
                        font.wordSpacing: 0
                    }

                    // Separator
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.preferredWidth: biApplicationWindowId.width * 0.0012
                        Layout.minimumWidth: biApplicationWindowId.width * 0.0012
                        Layout.maximumWidth: biApplicationWindowId.width * 0.0012
                        Layout.topMargin: biApplicationWindowId.height * 0.0055
                        Layout.minimumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.maximumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.preferredHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        color: "#aaaaaa"
                    }

                    Label {
                        id: biFooterLBmsId
                        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                        Layout.fillWidth: true
                        Layout.maximumWidth: biApplicationWindowId.width * 0.275
                        Layout.leftMargin: biApplicationWindowId.width * 0.00625
                        Layout.topMargin: biApplicationWindowId.height * (-0.003)

                        width: Layout.maximumWidth
                        height: font.pixelSize
                        text: sPort.connBMSFlag? qsTr("BMS Connection: Connected"):qsTr("BMS Connection: Disconnected")
                        font.pixelSize: biApplicationWindowId.height * 0.02
                        color: "#ffffff"
                        renderType: Text.QtRendering;
                        font.capitalization: Font.MixedCase
                        font.hintingPreference: Font.PreferFullHinting
                        font.bold: false
                        font.family: localFontId.name
                        font.italic: false
                        font.weight: Font.Thin
                        font.kerning: true
                        font.letterSpacing: 0
                        font.overline: false
                        font.preferShaping: true
                        font.wordSpacing: 0
                    }

                    // Separator
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.preferredWidth: biApplicationWindowId.width * 0.0012
                        Layout.minimumWidth: biApplicationWindowId.width * 0.0012
                        Layout.maximumWidth: biApplicationWindowId.width * 0.0012
                        Layout.topMargin: biApplicationWindowId.height * 0.0055
                        Layout.minimumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.maximumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.preferredHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        color: "#aaaaaa"
                    }

                    BiCommIndicator {
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.maximumWidth: biApplicationWindowId.height * 0.128
                        Layout.preferredWidth:biApplicationWindowId.height * 0.128
                        Layout.minimumWidth: biApplicationWindowId.height * 0.128
                        Layout.topMargin: biApplicationWindowId.height * 0.0095
                        biSize: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.019
                    }

                    // Separator
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.preferredWidth: biApplicationWindowId.width * 0.0012
                        Layout.minimumWidth: biApplicationWindowId.width * 0.0012
                        Layout.maximumWidth: biApplicationWindowId.width * 0.0012
                        Layout.topMargin: biApplicationWindowId.height * 0.0055
                        Layout.minimumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.maximumHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        Layout.preferredHeight: biApplicationWindowId.height * 0.04 - biApplicationWindowId.height * 0.011
                        color: "#aaaaaa"
                    }

                    Label {
                        id: biTimestampLableId
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.fillWidth: true
                        Layout.maximumWidth: biApplicationWindowId.width * 0.3125
                        Layout.rightMargin: biApplicationWindowId.width * 0.0125
                        Layout.topMargin: biApplicationWindowId.height * (-0.003)

                        width: implicitWidth
                        height: font.pixelSize
                        text: ((sPort.connBMSFlag) && (sPort.dataReadyFlag))?
                                  qsTr("BMS Timestamp: " + new Date(946677600000 + dataProfile.masterLifeTimeCounter * 1000).toLocaleString(Qt.locale(), "yyyy MM dd HH:mm:ss")):
                                  qsTr("BMS Timestamp: ---- -- -- --:--:--")
                        font.pixelSize: biApplicationWindowId.height * 0.02
                        color: "#ffffff"
                        renderType: Text.QtRendering;
                        horizontalAlignment: Qt.AlignRight
                        font.capitalization: Font.MixedCase
                        font.hintingPreference: Font.PreferFullHinting
                        font.bold: false
                        font.family: localFontId.name
                        font.italic: false
                        font.weight: Font.Thin
                        font.kerning: true
                        font.letterSpacing: 0
                        font.overline: false
                        font.preferShaping: true
                        font.wordSpacing: 0
                    }
                }
            }
        }
    }
}
