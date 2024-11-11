import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

ComboBox {
    property int biWidth:120
    property int biTextSize:8

    id: biComboBoxId
    width:biWidth
    font.pointSize: biTextSize

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    topInset: 0
    bottomInset: 0
    antialiasing: true

    Material.theme: Material.Light
    Material.accent: "#184180"
    Material.background: "#ffffff"
    FontLoader { id: localFontId; source: "tahoma.ttf" }

    delegate: ItemDelegate {
        id: biItemDelegateId
        width: biComboBoxId.width
        height: 21
        topPadding: 0
        bottomPadding: 0
        leftPadding: 0
        rightPadding: 0
        antialiasing: true

        contentItem: Text {
            height:21
            width:biComboBoxId.width-20
            text: modelData
            renderType: Text.QtRendering;
            color: biItemDelegateId.highlighted ? "#ffffff" : "#000000"
            font: biComboBoxId.font
            verticalAlignment: Text.AlignVCenter
            leftPadding: 10
            rightPadding: 0
            topPadding: 0
            bottomPadding: 0
            antialiasing: true
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

        highlighted: biComboBoxId.highlightedIndex===index

        background: Rectangle {
            anchors.fill: biItemDelegateId
            color: biItemDelegateId.highlighted ? "#184180" : "#ffffff"
            antialiasing: true
        }
    }


    indicator: Item{
        Canvas {
            id: biCanvasId1
            width: biComboBoxId.width-x-1
            height: biComboBoxId.availableHeight-2
            x:biComboBoxId.width-24
            y: biComboBoxId.topPadding + (biComboBoxId.availableHeight - height) / 2
            antialiasing: true

            Connections {
                target: biComboBoxId
                function onPressedChanged() { biCanvasId1.requestPaint(); }
            }

            onPaint: {
                var ctx = biCanvasId1.getContext('2d')
                ctx.rect(0, 0, biComboBoxId.width-biCanvasId1.x, biComboBoxId.availableHeight-2)
                ctx.fillStyle = "#184180"
                ctx.fill()
            }
        }
        Canvas {
            id: biCanvasId2
            width: 12
            height: 8
            x: biComboBoxId.width-18
            y: biComboBoxId.topPadding + (biComboBoxId.availableHeight - height) / 2
            antialiasing: true

            Connections {
                target: biComboBoxId
                function onPressedChanged() { biCanvasId2.requestPaint(); }
            }

            onPaint: {
                var ctx = biCanvasId2.getContext('2d')
                ctx.moveTo(0, 0);
                ctx.lineTo(12, 0);
                ctx.lineTo(12/2, 8);
                ctx.closePath();
                ctx.fillStyle = "#ffffff"
                ctx.fill()
            }
        }
    }

    contentItem: Text {
        height:21
        leftPadding: 10
        rightPadding: biComboBoxId.indicator.width + biComboBoxId.spacing
        text: biComboBoxId.displayText
        font: biComboBoxId.font
        renderType: Text.QtRendering;
        color: "#000000"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        antialiasing: true
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

    background: Rectangle {
        implicitWidth: biComboBoxId.width
        implicitHeight: 21
        border.color: "#184180"
        border.width: 1
        radius: 0
        antialiasing: true
    }

    popup: Popup {
        y: biComboBoxId.height - 1
        width: biComboBoxId.width
        implicitHeight: contentItem.implicitHeight
        padding: 1
        visible: false
        font: biComboBoxId.font

        contentItem: ListView {
            clip: true
            implicitHeight: 21*4
            model: biComboBoxId.popup.visible ? biComboBoxId.delegateModel : null
            currentIndex: biComboBoxId.highlightedIndex
            antialiasing: true

            ScrollBar.vertical: ScrollBar {
                active: true
                orientation: Qt.Vertical
                policy: "AlwaysOn"
                antialiasing: true

                contentItem: Rectangle {
                    implicitWidth: 10
                    radius: 0
                    color: "#184180"
                    antialiasing: true
                }

                background: Rectangle{
                    color:"#e8e8e8"
                    antialiasing: true
                }
            }
        }

        background: Rectangle {
            border.color: "#184180"
            radius: 0
            antialiasing: true
        }
    }
}
