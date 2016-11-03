import QtQuick 2.7

Rectangle{
    height: textInput.height
    color: "white"
    border.width: 1
    border.color: textInput.activeFocus ? "blue" : "black"

    property alias readOnly: textInput.readOnly
    property alias text: textInput.text

    TextInput{
        id: textInput
        anchors.fill: parent
        activeFocusOnPress: ! readOnly
        height: font.pixelSize + padding * 2
        padding: 5
    }
}
