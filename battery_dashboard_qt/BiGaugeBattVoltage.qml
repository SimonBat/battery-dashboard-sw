import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item {
    property int biMinValue: 0
    property int biMaxValue: 100
    property int biTickStepSize: 10
    property bool biEnabled: true
    property int biPrecision: 2
    property real biValue: biMinValue
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

        anchors.fill: parent
        anchors.centerIn: parent

        minimumValue: biGaugeVoltageId.biGaugeMin
        maximumValue: biGaugeVoltageId.biGaugeMax
        stepSize: 1
        value: biGaugeVoltageId.biValue
        antialiasing: true

        style: CircularGaugeStyle {
            id: biGaugeStyleId

            labelStepSize: biGaugeVoltageId.biTickStepSize
            tickmarkStepSize: biGaugeVoltageId.biTickStepSize
            minimumValueAngle: -145
            maximumValueAngle: 145
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
                font.pixelSize: Math.max(6, outerRadius * 0.125)
                text: styleData.value
                color: (styleData.value >= biGaugeVoltageId.biMaxValue) ? "#e9967a":((styleData.value <= biGaugeVoltageId.biMinValue)? "#e9967a":"#ffffff")
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
                    function onBiMinValueChanged() { biGaugeBackgroundCanvasId.requestPaint(); }
                    function onBiMaxValueChanged() { biGaugeBackgroundCanvasId.requestPaint(); }
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
                    id: biGaugeNameHId

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.verticalCenter
                    anchors.topMargin: outerRadius * 0.42

                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0

                    font.pixelSize: Math.max(6, outerRadius * 0.1)
                    text: qsTr("BATTERY")
                    color: "#e0e0e0"
                    horizontalAlignment: Text.AlignRight
                    renderType: Text.QtRendering;
                    antialiasing: true
                }

                Text {
                    id: biGaugeNameLId

                    horizontalAlignment: Text.AlignRight
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: biGaugeNameHId.bottom
                    anchors.topMargin: 0

                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0

                    font.pixelSize: Math.max(6, outerRadius * 0.1)
                    text: qsTr("VOLTAGE")
                    color: "#e0e0e0"
                    renderType: Text.QtRendering;
                    antialiasing: true
                }

                Text {
                    anchors.top: biGaugeNameLId.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: outerRadius * 0.02

                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0

                    text: ((biGaugeVoltageId.biEnabled)? qsTr(biGaugeVoltageId.biValue.toFixed(biGaugeVoltageId.biPrecision)):qsTr("-")) + qsTr(" V")
                    color: (biGaugeVoltageId.biValue >= biGaugeVoltageId.biMaxValue)? "#e9967a":((biGaugeVoltageId.biValue <= biGaugeVoltageId.biMinValue)? "#e9967a":"#ffffff")
                    font.pixelSize: Math.max(6, outerRadius * 0.15)
                    renderType: Text.QtRendering;
                    antialiasing: true
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
