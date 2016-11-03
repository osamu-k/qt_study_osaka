import QtQuick 2.7

Rectangle{
    color: "white"
    border.width: 1
    border.color: textEdit.activeFocus ? "blue" : "black"

    property alias readOnly: textEdit.readOnly
    property alias text: textEdit.text

    function append(text){
        textEdit.append(text)
    }

    TextEdit{
        id: textEdit
        anchors.fill: parent
        activeFocusOnPress: ! readOnly
        textMargin: 5
    }
}
