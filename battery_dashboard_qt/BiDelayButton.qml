import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item {
    property int biTextSize: biSize * 0.18
    property alias biText: biDButtonId.text
    property int biSize: 65
    property int biDelay: 500
    property alias biActivatedFlag: biDButtonId.checked
    property bool biAutoReset: false

    id: biDelayButtonId

    Material.theme: Material.Light
    Material.accent: "#184180"
    Material.background: "#ffffff"
    FontLoader { id: localFontId; source: "tahoma.ttf" }

    height: biSize
    width: height
    antialiasing: true

    DelayButton {
        id: biDButtonId

        height: biDelayButtonId.biSize
        width: biDelayButtonId.biSize
        delay: biDelayButtonId.biDelay
        antialiasing: true

        style: DelayButtonStyle {
            label: Text {
                text: biDButtonId.text
                color: "#252525"
                renderType: Text.QtRendering;
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                font.pixelSize: biDelayButtonId.biTextSize
                font.bold: true
                antialiasing: true
                font.capitalization: Font.MixedCase
                font.hintingPreference: Font.PreferFullHinting
                font.family: localFontId.name
                font.italic: false
                font.weight: Font.Thin
                font.kerning: true
                font.letterSpacing: 0
                font.overline: false
                font.preferShaping: true
                font.wordSpacing: 0
            }

            foreground: Rectangle {
                implicitWidth: biDelayButtonId.biSize
                implicitHeight: biDelayButtonId.biSize
                color: "#a8a8a8"
                radius: biDelayButtonId.biSize / 2
                width: biDelayButtonId.biSize
                height: biDelayButtonId.biSize
                anchors.centerIn: parent
                antialiasing: true

                Rectangle{
                    anchors.centerIn: parent
                    implicitWidth: biDelayButtonId.biSize - 4
                    implicitHeight: biDelayButtonId.biSize - 4
                    color: "#e8e8e8"
                    radius: (biDelayButtonId.biSize - 4) / 2
                    antialiasing: true
                }

                Canvas {
                    id: biCanvasId
                    anchors.fill: parent
                    antialiasing: true

                    Connections {
                        target: biDButtonId
                        function onProgressChanged() { biCanvasId.requestPaint(); }
                    }

                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.clearRect(0, 0, width, height)
                        ctx.strokeStyle = "#e9967a"
                        ctx.lineWidth = biDelayButtonId.biSize / 20

                        ctx.beginPath()
                        var startAngle = Math.PI/2
                        var endAngle = startAngle + control.progress * 2 * Math.PI
                        ctx.arc(width / 2, height / 2, width / 2 - ctx.lineWidth / 2 - 2, startAngle, endAngle)
                        ctx.stroke()
                    }
                }
            }
        }

        onActivated: {
            if(biDelayButtonId.biAutoReset){ biResetTimerId.running = true; }
        }

        Timer {
            id: biResetTimerId
            interval: biDelayButtonId.biDelay
            running: false
            repeat: false
            onTriggered: { biDButtonId.checked = false; }
        }
    }
}
