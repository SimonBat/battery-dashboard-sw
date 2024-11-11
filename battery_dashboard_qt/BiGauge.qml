import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item{
    property int biHeight: parent.height
    property int biWidth: 20
    property int biTickmarkStepSize: 20
    property int biMinorTickmarkCnt: 4
    property int biMinimumValue: -40
    property int biMaximumValue: 120
    property int biMaxWarningValue: 90
    property int biMinWarningValue: 0
    property int biPrecision: 1
    property alias biValue: biGaugeId.value
    property string biUnit: ""

    id: biGaugeItemId

    Material.theme: Material.Light
    Material.accent: "#184180"
    Material.background: "#ffffff"

    height: biHeight
    width: biGaugeId.implicitWidth
    antialiasing: true

    Gauge {
        id: biGaugeId

        height: biHeight - biGaugeTextId.height
        tickmarkStepSize: biGaugeItemId.biTickmarkStepSize

        minorTickmarkCount: biGaugeItemId.biMinorTickmarkCnt
        minimumValue: biGaugeItemId.biMinimumValue
        maximumValue: biGaugeItemId.biMaximumValue
        tickmarkAlignment: Qt.AlignLeft
        antialiasing: true

        Behavior on value {
            NumberAnimation {
                duration: 1000
                easing.type: Easing.OutQuint
            }
        }

        style: GaugeStyle {
            valueBar: Rectangle {
                color: (biGaugeId.value >= biGaugeItemId.biMaxWarningValue)? "#e9967a":((biGaugeId.value <= biGaugeItemId.biMinWarningValue)? "#e9967a":"#e8e8e8")
                implicitWidth: biWidth
                antialiasing: true
            }

            minorTickmark: Item {
                implicitWidth: biWidth * 0.3
                implicitHeight: biHeight * 0.006
                antialiasing: true

                Rectangle {
                    color: (styleData.value >= biGaugeItemId.biMaxWarningValue)? "#e9967a" :((styleData.value <= biGaugeItemId.biMinWarningValue)? "#e9967a":"#e8e8e8")
                    anchors.fill: parent
                    anchors.leftMargin: biWidth * 0.09
                    anchors.rightMargin: biWidth * 0.03
                    antialiasing: true
                }
            }

            tickmark: Item {
                implicitWidth: biWidth * 0.5
                implicitHeight: biHeight * 0.01
                antialiasing: true

                Rectangle {
                    color: (styleData.value >= biGaugeItemId.biMaxWarningValue)? "#e9967a":((styleData.value <= biGaugeItemId.biMinWarningValue)? "#e9967a":"#e8e8e8")
                    anchors.fill: parent
                    anchors.leftMargin: biWidth * 0.15
                    anchors.rightMargin: biWidth * 0.05
                    antialiasing: true
                }
            }

            tickmarkLabel: Text {
                font.pixelSize: biHeight * 0.07
                text: styleData.value
                color: (styleData.value >= biGaugeItemId.biMaxWarningValue)? "#e9967a":((styleData.value <= biGaugeItemId.biMinWarningValue)? "#e9967a":"#e8e8e8")
                antialiasing: true
                renderType: Text.QtRendering;
                leftPadding: 0
                rightPadding: 0
            }
        }
    }

    Text {
        id: biGaugeTextId

        anchors.right: biGaugeId.right
        anchors.top: biGaugeId.bottom

        topPadding: biHeight * 0.005
        bottomPadding: 0
        leftPadding: 0
        rightPadding: 0

        font.pixelSize: biHeight * 0.07
        text: qsTr(biGaugeId.value.toFixed(biGaugeItemId.biPrecision) + " " + biUnit)
        color: (biGaugeId.value >= biGaugeItemId.biMaxWarningValue)? "#e9967a":((biGaugeId.value <= biGaugeItemId.biMinWarningValue)? "#e9967a":"#e8e8e8")
        horizontalAlignment: Text.AlignRight
        renderType: Text.QtRendering;
        antialiasing: true
    }
}
