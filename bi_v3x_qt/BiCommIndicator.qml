import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

Item {
    property real biSize: 10
    property bool biTxBlinkTrigger: sPort.txBlinkTrigger
    property bool biRxBlinkTrigger: sPort.rxBlinkTrigger

    onBiTxBlinkTriggerChanged: {
        if(biTxBlinkTrigger)
        {
            biTxTimerId.start();
            biIndicatorTxStatusId.color = "#e9967a"
        }
    }

    onBiRxBlinkTriggerChanged: {
        if(biRxBlinkTrigger)
        {
            biRxTimerId.start();
            biIndicatorRxStatusId.color = "#e9967a"
        }
    }

    id: biCommIndicatorId

    Material.theme: Material.Light
    Material.accent: "#252525"
    Material.background: "#ffffff"
    FontLoader { id: localFontId; source: "tahoma.ttf" }

    Label {
        id: biIndicatorTxLabelId

        leftPadding: biSize * 0.5
        rightPadding: biSize * 0.4
        topPadding: biSize * (-0.025)
        height: font.pointSize
        text: qsTr("TX")
        font.pixelSize: biSize * 0.8
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

    Rectangle {
        id: biIndicatorTxId
        anchors.left: biIndicatorTxLabelId.right
        height: biSize
        width: biSize
        color: "#ffffff"
        radius: biSize * 0.2

        Rectangle {
            id: biIndicatorTxStatusId
            anchors.centerIn: parent
            height: biSize * 0.8
            width: biSize * 0.8
            color: "#252525"
            radius: biSize * 0.2
        }
    }

    Label {
        id: biIndicatorRxLabelId
        anchors.left: biIndicatorTxId.right
        leftPadding: biSize * 0.5
        rightPadding: biSize * 0.4
        topPadding: biSize * (-0.025)
        height: font.pointSize
        text: qsTr("RX")
        font.pixelSize: biSize * 0.8
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

    Rectangle {
        id: biIndicatorRxId
        anchors.left: biIndicatorRxLabelId.right
        height: biSize
        width: biSize
        color: "#ffffff"
        radius: biSize * 0.2

        Rectangle {
            id: biIndicatorRxStatusId
            anchors.centerIn: parent
            height: biSize * 0.8
            width: biSize * 0.8
            color: "#252525"
            radius: biSize * 0.2
        }
    }

    Timer {
        id: biTxTimerId
        interval: 50
        running: true
        repeat: false
        onTriggered: {
            biIndicatorTxStatusId.color = "#252525"
            sPort.txBlinkTrigger = false;
        }
    }

    Timer {
        id: biRxTimerId
        interval: 50
        running: true
        repeat: false
        onTriggered: {
            biIndicatorRxStatusId.color = "#252525"
            sPort.rxBlinkTrigger = false;
        }
    }
}
