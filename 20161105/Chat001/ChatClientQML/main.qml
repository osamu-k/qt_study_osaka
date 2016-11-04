import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 500
    height: 400
    title: qsTr("Chat Client QML")

    Rectangle{
        anchors.fill: parent
        color: "lightGray"

        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            SplitView{
                Layout.fillWidth: true
                Layout.fillHeight: true
                orientation: Qt.Vertical

                MyTextEdit{
                    id: textLog
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    readOnly: true
                    focus: false
                }

                MyTextEdit{
                    id: textInput
                    Layout.fillWidth: true
                    height: parent.height * 0.3
                }
            }
            RowLayout{
                spacing: 5
                Button{
                    text: qsTr("Connect")
                    onClicked: {
                        chatClient.connectToHost(inputHost.text,inputPort.text)                  }
                }
                Button{
                    text: qsTr("Disconnect")
                    onClicked:{
                        chatClient.disconnectFromHost()
                    }
                }
                Item{
                    Layout.fillWidth: true
                }
                Button{
                    text: qsTr("Clear")
                    onClicked: {
                        textInput.text = ""
                    }
                }
                Button{
                    text: qsTr("Send")
                    onClicked: {
                        chatClient.send(textInput.text)
                        textInput.text = ""
                    }
                }
            }
            RowLayout{
                Layout.fillHeight: false
                spacing: 5
                Text{
                    text: qsTr("host")
                }
                MyTextInput{
                    id: inputHost
                    Layout.fillWidth: true
                    text: "localhost"
                }
                Text{
                    text: qsTr("port")
                }
                MyTextInput{
                    id: inputPort
                    Layout.fillWidth: true
                    text: "12345"
                }
            }
        }
    }
    Connections{
        target: chatClient
        onReceived:{
            textLog.append(message)
        }
    }
}
