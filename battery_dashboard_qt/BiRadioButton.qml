import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

RadioButton{
    property alias biText: biRadioButtonId.text
    property real biTextSize: biSize * 0.75
    property real biSize: 14

    id: biRadioButtonId
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

    Layout.alignment: Qt.AlignTop
    Layout.fillHeight: true
    Layout.topMargin: biSize * 0.143
    Layout.bottomMargin: biSize * 0.143
    Layout.leftMargin: biSize * 0.429
    antialiasing: true

    Material.theme: Material.Light
    Material.accent: "#ffffff"
    Material.background: "#252525"

    indicator:Rectangle {
        id: centerId
        implicitWidth: biSize * 1.286
        implicitHeight: biSize * 1.286
        border.width: biSize * 0.0714
        x: 0
        y: biRadioButtonId.height / 2 - height / 2
        color: "#252525"
        border.color: "#252525"

        Rectangle {
            implicitWidth: biSize
            implicitHeight: biSize
            border.width: biSize * 0.0714
            x: 0
            y: biRadioButtonId.height / 2 - height / 2
            radius: biSize * 0.571
            border.color: "#ffffff"
            antialiasing: true

            Rectangle {
                width: biSize * 0.5
                height: biSize * 0.5
                x: biSize * 0.25
                y: biSize * 0.25
                radius: biSize * 0.25
                color: "#e9967a"
                border.color: "#353535"
                visible: biRadioButtonId.checked
                antialiasing: true
            }
        }
    }

    contentItem: Label {
        id: biTextId
        text: qsTr(biRadioButtonId.text)
        font: biRadioButtonId.font
        color: "#ffffff"
        renderType: Label.QtRendering;
        leftPadding: biSize * 1.57
        topPadding: biSize * 0.143
        bottomPadding: 0
        antialiasing: true
    }
}
