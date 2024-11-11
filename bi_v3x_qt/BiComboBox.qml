import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

ComboBox {
    property real biWidth: 120
    property real biHeight: 17
    property real biTextSize: biHeight * 0.6

    id: biComboBoxId
    width: biWidth
    FontLoader { id: localFontId; source: "tahoma.ttf" }
    font.pixelSize: biTextSize
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

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    topInset: 0
    bottomInset: 0
    antialiasing: true

    Material.theme: Material.Light
    Material.accent: "#353535"
    Material.background: "#ffffff"

    delegate: ItemDelegate {
        id: biItemDelegateId
        width: biWidth
        height: biHeight
        topPadding: 0
        bottomPadding: 0
        leftPadding: 0
        rightPadding: 0
        antialiasing: true

        contentItem: Text {
            height: biHeight
            width: biWidth - biWidth * 0.167
            text: modelData
            renderType: Text.QtRendering;
            color: biItemDelegateId.highlighted? "#252525":"#ffffff"
            font: biComboBoxId.font
            verticalAlignment: Text.AlignVCenter
            leftPadding: biWidth * 0.083
            rightPadding: 0
            topPadding: 0
            bottomPadding: 0
            antialiasing: true
        }

        highlighted: (biComboBoxId.highlightedIndex === index)

        background: Rectangle {
            anchors.fill: biItemDelegateId
            color: biItemDelegateId.highlighted ? "#e9967a":"#353535"
            antialiasing: true
            radius: biHeight * 0.235
        }
    }

    indicator: Item {
        Canvas {
            id: biCanvasId1
            width: height
            height: biHeight * 0.8
            x: biWidth - height - (biHeight - height) / 2
            y: (biHeight - height) / 2
            antialiasing: true

            Connections {
                target: biComboBoxId
                function onPressedChanged() { biCanvasId1.requestPaint(); }
                function onBiHeightChanged() { biCanvasId1.requestPaint(); }
            }

            onPaint: {
                var ctx = biCanvasId1.getContext('2d')
                ctx.roundedRect(0, 0, biCanvasId1.width, biCanvasId1.height, biHeight * 0.2, biHeight * 0.2)
                ctx.fillStyle = "#ffffff"
                ctx.fill()
            }
        }

        Canvas {
            id: biCanvasId2
            width: height
            height: biHeight * 0.6
            x: biWidth - width * 1.3
            y: biHeight - height * 1.15
            antialiasing: true

            Connections {
                target: biComboBoxId
                function onPressedChanged() { biCanvasId2.requestPaint(); }
                function onBiHeightChanged() { biCanvasId2.requestPaint(); }
            }

            onPaint: {
                var ctx = biCanvasId2.getContext('2d')
                ctx.beginPath();
                ctx.moveTo(0, 0);

                ctx.lineTo(biCanvasId2.width, 0);
                ctx.lineTo(biCanvasId2.width * 0.5, biCanvasId2.width * 0.7);
                ctx.closePath();
                ctx.fillStyle = "#353535"
                ctx.fill()
            }
        }
    }

    contentItem: Text {
        height: biHeight
        leftPadding: biWidth * 0.083
        rightPadding: biComboBoxId.indicator.width + biComboBoxId.spacing
        text: biComboBoxId.displayText
        font: biComboBoxId.font
        renderType: Text.QtRendering;
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        antialiasing: true
    }

    background: Rectangle {
        implicitWidth: biWidth
        implicitHeight: biHeight
        border.color: "#ffffff"
        color: "#353535"
        border.width: biHeight * 0.0588
        radius: biHeight * 0.235
        antialiasing: true
    }

    popup: Popup {
        y: biHeight - 1
        width: biWidth
        implicitHeight: contentItem.implicitHeight
        padding: biHeight * 0.0588
        visible: false
        font: biComboBoxId.font

        contentItem: ListView {
            clip: true
            implicitHeight: biHeight*4
            model: biComboBoxId.popup.visible ? biComboBoxId.delegateModel:null
            currentIndex: biComboBoxId.highlightedIndex
            antialiasing: true

            ScrollBar.vertical: ScrollBar {
                active: true
                orientation: Qt.Vertical
                policy: "AlwaysOn"
                antialiasing: true

                contentItem: Rectangle {
                    implicitWidth: biWidth * 0.083
                    radius: biHeight * 0.235
                    color: "#353535"
                    antialiasing: true
                }

                background: Rectangle {
                    color: "#e8e8e8"
                    antialiasing: true
                    radius: biHeight * 0.235
                }
            }
        }

        background: Rectangle {
            border.color: "#ffffff"
            color: "#353535"
            radius: biHeight * 0.235
            antialiasing: true
        }
    }
}
