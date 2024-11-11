import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item {
    property real biMinValueF: 2.5
    property real biMaxValueF: 4.2
    property real biTickStepSizeF: 0.2
    property real biValueF: biMinValueF
    readonly property int biMinValue: Math.floor(biMinValueF * 10)
    readonly property int biMaxValue: Math.ceil(biMaxValueF * 10)
    readonly property int biTickStepSize: Math.floor(biTickStepSizeF * 10)
    property bool biEnabled: true
    property int biPrecision: 3
    property string biCellName: ""
    readonly property real biValue: biValueF*10
    readonly property int biGaugeMin: findGaugeMinValue(Math.round(biMinValue))
    readonly property int biGaugeMax: findGaugeMaxValue(Math.round(biMaxValue))
    property alias biStepSize: biGaugeId.stepSize

    id: biGaugeVoltageId

    Material.theme: Material.Light
    Material.accent: "#184180"
    Material.background: "#ffffff"
    antialiasing: true

    function findGaugeMinValue(minValue) {
        var rank = 0;
        var result = 0;
        var temp = Math.floor(minValue);

        while(minValue >= 1){minValue /= 10; rank++;}
        result = Math.floor(minValue * Math.pow(10, (rank - 1))) * 10 - biGaugeVoltageId.biTickStepSize;
        while(result < (temp - (biGaugeVoltageId.biTickStepSize * 2))){result += biGaugeVoltageId.biTickStepSize;}
        if(result < 0){result = 0;}

        return result;
    }

    function findGaugeMaxValue(maxValue) {
        var rank = 0;
        var result = 0;
        var temp = Math.ceil(maxValue);

        while(maxValue >= 1){maxValue /= 10; rank++;}
        result = Math.floor(maxValue * Math.pow(10, (rank - 1))) * 10;
        while(result < (temp + biGaugeVoltageId.biTickStepSize)){result += biGaugeVoltageId.biTickStepSize;}

        return result;
    }

    CircularGauge {
        id:biGaugeId

        anchors.centerIn: parent
        width: parent.width
        height: parent.height * 2

        minimumValue: biGaugeVoltageId.biGaugeMin
        maximumValue: biGaugeVoltageId.biGaugeMax
        stepSize: 1
        value: biGaugeVoltageId.biValue
        antialiasing: true

        style: CircularGaugeStyle {
            id: biGaugeStyleId

            labelStepSize: biGaugeVoltageId.biTickStepSize
            tickmarkStepSize: biGaugeVoltageId.biTickStepSize
            minimumValueAngle: -90
            maximumValueAngle: 90
            labelInset: outerRadius * 0.2
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
                antialiasing: true

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
                                degreesToRadians(valueToAngle(biGaugeVoltageId.biMinValue) - 90), degreesToRadians(valueToAngle(biGaugeVoltageId.biMaxValue) - 90));
                        ctx.stroke();
                    }
                }
            }

            tickmarkLabel: Text {
                font.pixelSize: Math.max(6, outerRadius * 0.12)
                text: (styleData.value / 10).toFixed(1)
                color: (styleData.value >= biGaugeVoltageId.biMaxValue)? "#e9967a":((styleData.value <= biGaugeVoltageId.biMinValue)? "#e9967a":"#ffffff")
                antialiasing: true
                renderType: Text.QtRendering;

            }

            tickmark: Rectangle {
                visible: true
                implicitWidth: outerRadius * 0.03
                antialiasing: true
                implicitHeight: outerRadius * 0.08
                color: (styleData.value >= biGaugeVoltageId.biMaxValue)? "#e9967a":((styleData.value <= biGaugeVoltageId.biMinValue)? "#e9967a":"#ffffff")
            }

            minorTickmark: Rectangle {
                visible: (styleData.value < biGaugeVoltageId.biMaxValue) && (styleData.value > biGaugeVoltageId.biMinValue)
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
                    target: biGaugeVoltageId
                    function onBiMinValueFChanged() { biGaugeBackgroundCanvasId.requestPaint(); }
                    function onBiMaxValueFChanged() { biGaugeBackgroundCanvasId.requestPaint(); }
                }

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.reset();

                    ctx.beginPath();
                    ctx.strokeStyle = "#e9967a";
                    ctx.lineWidth = outerRadius * 0.045;

                    ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
                            degreesToRadians(valueToAngle(biGaugeVoltageId.biMaxValue) - 90), degreesToRadians(valueToAngle(biGaugeVoltageId.biGaugeMax) - 90));
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.strokeStyle = "#e9967a";
                    ctx.lineWidth = outerRadius * 0.045;

                    ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
                            degreesToRadians(valueToAngle(biGaugeVoltageId.biGaugeMin) - 90), degreesToRadians(valueToAngle(biGaugeVoltageId.biMinValue) - 90));
                    ctx.stroke();
                }

                Text {
                    id: biGaugeNameId

                    anchors.top: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.topMargin: outerRadius * 0.22
                    anchors.leftMargin: outerRadius * 0.25

                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0

                    font.pixelSize: Math.max(6, outerRadius * 0.11)
                    text: qsTr(biGaugeVoltageId.biCellName + " CELL VOLTAGE")
                    color: "#e0e0e0"
                    horizontalAlignment: Text.AlignRight
                    renderType: Text.QtRendering;
                }

                Text {
                    anchors.left: biGaugeNameId.right
                    anchors.top: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: outerRadius * 0.2
                    anchors.leftMargin: outerRadius * 0.1

                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0

                    text: ((biGaugeVoltageId.biEnabled)? qsTr(biGaugeVoltageId.biValueF.toFixed(biGaugeVoltageId.biPrecision)):qsTr("-")) + qsTr(" V")
                    color: (biGaugeVoltageId.biValue >= biGaugeVoltageId.biMaxValue)? "#e9967a":((biGaugeVoltageId.biValue <= biGaugeVoltageId.biMinValue)? "#e9967a":"#ffffff")
                    font.pixelSize: Math.max(6, outerRadius * 0.15)
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
