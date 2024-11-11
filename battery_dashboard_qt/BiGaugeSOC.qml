import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item {
    property int biMinValue: 0
    property int biTickStepSize: 10
    property bool biEnabled: true
    property int biPrecision: 0
    property int biValue: biMinValue
    readonly property int biGaugeMin: 0
    readonly property int biGaugeMax: 100
    property alias biStepSize: biGaugeId.stepSize

    id: biGaugeSOCId

    Material.theme: Material.Light
    Material.accent: "#184180"
    Material.background: "#ffffff"

    CircularGauge {
        id: biGaugeId

        anchors.centerIn: parent
        width: parent.width
        height: parent.height * 2

        minimumValue: biGaugeSOCId.biGaugeMin
        maximumValue: biGaugeSOCId.biGaugeMax
        stepSize: 1
        value: biGaugeSOCId.biValue
        antialiasing: true

        style: CircularGaugeStyle {
            id: biGaugeStyleId

            labelStepSize: biGaugeSOCId.biTickStepSize
            tickmarkStepSize: biGaugeSOCId.biTickStepSize
            minimumValueAngle: -90
            maximumValueAngle: 90
            labelInset: outerRadius * 0.22
            tickmarkInset: outerRadius * 0.005
            minorTickmarkInset: outerRadius * 0.005

            needle: Rectangle {
                y: outerRadius * 0.22
                implicitWidth: outerRadius * 0.034
                implicitHeight: outerRadius * 1.12
                antialiasing: true
                color: "#e0e0e0"
            }

            foreground:Item {
                anchors.fill: parent

                Rectangle {
                    width: outerRadius * 0.18
                    height: width
                    radius: width / 2
                    color: "#a8a8a8"
                    anchors.centerIn: parent
                    antialiasing: true
                }

                Canvas {
                    anchors.fill: parent
                    antialiasing: true
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();
                        ctx.beginPath();
                        ctx.lineWidth = outerRadius * 0.01;
                        ctx.strokeStyle = "#a8a8a8";
                        ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
                                degreesToRadians(valueToAngle(biGaugeSOCId.biMinValue) - 90), degreesToRadians(valueToAngle(biGaugeSOCId.biGaugeMax) - 90));
                        ctx.stroke();
                    }
                }
            }

            tickmarkLabel: Text {
                font.pixelSize: Math.max(6, outerRadius * 0.125)
                text: styleData.value
                color: (styleData.value <= biGaugeSOCId.biMinValue)? "#e9967a":"#ffffff"
                antialiasing: true
                renderType: Text.QtRendering;
            }

            tickmark: Rectangle {
                visible: true
                implicitWidth: outerRadius * 0.03
                antialiasing: true
                implicitHeight: outerRadius * 0.08
                color: (styleData.value <= biGaugeSOCId.biMinValue)? "#e9967a":"#ffffff"
            }

            minorTickmark: Rectangle {
                visible: (styleData.value < biGaugeSOCId.biGaugeMax) && (styleData.value > biGaugeSOCId.biMinValue)
                implicitWidth: outerRadius * 0.015
                antialiasing: true
                implicitHeight: outerRadius * 0.05
                color: "#ffffff"
            }

            function degreesToRadians(degrees) {
                return degrees * (Math.PI / 180);
            }

            background:
                Canvas {
                id: biGaugeBackgroundCanvasId
                antialiasing: true

                Connections {
                    target: biGaugeSOCId
                    function onBiMinValueChanged() { biGaugeBackgroundCanvasId.requestPaint(); }
                }

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.reset();

                    ctx.beginPath();
                    ctx.strokeStyle = "#e9967a";
                    ctx.lineWidth = outerRadius * 0.045;

                    ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
                            degreesToRadians(valueToAngle(biGaugeSOCId.biGaugeMax) - 90), degreesToRadians(valueToAngle(biGaugeSOCId.biGaugeMax) - 90));
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.strokeStyle = "#e9967a";
                    ctx.lineWidth = outerRadius * 0.045;

                    ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
                            degreesToRadians(valueToAngle(biGaugeSOCId.biGaugeMin) - 90), degreesToRadians(valueToAngle(biGaugeSOCId.biMinValue) - 90));
                    ctx.stroke();
                }

                Text {
                    id: biGaugeNameId

                    anchors.top: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.topMargin: outerRadius * 0.25
                    anchors.leftMargin: outerRadius * 0.65

                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0

                    font.pixelSize: Math.max(6, outerRadius * 0.15)
                    text: qsTr("SOC")
                    color: "#e0e0e0"
                    horizontalAlignment: Text.AlignRight
                    antialiasing: true
                    renderType: Text.QtRendering;
                }

                Text {
                    anchors.left: biGaugeNameId.right
                    anchors.top: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: outerRadius * 0.23
                    anchors.leftMargin: outerRadius * 0.05

                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0

                    text: ((biGaugeSOCId.biEnabled)? qsTr(biGaugeSOCId.biValue.toFixed(biGaugeSOCId.biPrecision)):qsTr("-")) + qsTr(" %")
                    color: (biGaugeSOCId.biValue <= biGaugeSOCId.biMinValue)? "#e9967a":"#ffffff"
                    font.pixelSize: Math.max(6, outerRadius * 0.2)
                    antialiasing: true
                    renderType: Text.QtRendering;
                }
            }
        }

        Behavior on value {
            NumberAnimation {
                duration: 1000
                easing.type: Easing.OutQuint
            }
        }
    }
}
