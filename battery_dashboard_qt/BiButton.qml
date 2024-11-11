import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

Button {
    property alias biText: biButtonId.text
    property real biTextSize: biHeight * 0.6
    property real biWidth: 85
    property real biHeight: 17

    id: biButtonId
    highlighted: true
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

    width: biWidth
    height: biHeight
    icon.height: height
    bottomInset: 0
    topInset: 0
    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0
    spacing: 0
    antialiasing: true

    Material.theme: Material.Light
    Material.accent: "#ffffff"
    Material.background: "#252525"

    contentItem: Text {
        id: biTextId
        font: biButtonId.font
        text: biButtonId.text
        renderType: Text.QtRendering;
        color: biButtonId.down ? "#252525":"#ffffff"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        antialiasing: true
    }

    background: Rectangle {
        implicitWidth: biButtonId.width
        implicitHeight: biHeight
        color: biButtonId.down ? "#e9967a":"#353535"
        border.color: "#ffffff"
        border.width: biHeight * 0.06
        radius: biHeight * 0.235
        antialiasing: true
    }
}
