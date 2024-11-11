import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

Label{
    property string biName: ""
    property color biColor: "#000000"
    property color biBackground: "#e8e8e8"
    property bool biEnabled: true
    property real biMaxWidth: biTextId.implicitWidth
    property real biTextSize: 8
    property int biTextLeftPadding: 0
    property int biTextRightPadding: 0

    id: biLabelNId

    Material.theme: Material.Light
    Material.accent: "#184180"
    Material.background: "#ffffff"
    FontLoader { id: localFontId; source: "tahoma.ttf" }

    topInset: 0
    bottomInset: 0
    leftInset: 0
    rightInset: 0

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    height: biTextId.implicitHeight
    width: Math.min(biTextId.implicitWidth, biMaxWidth)
    font.pixelSize: biTextSize
    antialiasing: true

    background: Rectangle {
        anchors.fill: parent
        color: biLabelNId.biBackground
        antialiasing: true
    }

    Text {
        id: biTextId

        anchors.fill: parent
        topPadding: 0
        bottomPadding: 0
        leftPadding: biTextLeftPadding
        rightPadding: biTextRightPadding

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

        text: (biLabelNId.biEnabled)? qsTr(biLabelNId.biName):qsTr("-")
        color: biLabelNId.biColor
        renderType: Text.QtRendering;
        horizontalAlignment: Text.AlignHLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        antialiasing: true
    }
}
