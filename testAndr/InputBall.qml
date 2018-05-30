import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Window 2.10
import QtQuick.Controls.Material 2.1
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3

Rectangle {
    id: ballForm
    x: 150
    y: root.header.width / 6
    width: root.header.width / 3 * 2
    color: "#cdcbd1"
    opacity: 0.0
    visible: false
    Layout.fillWidth: true
    Connections {
        target: root
        onSetupAsked: {
            ballForm.opacity = 1.0
            ballForm.visible = true
        }
    }
    GroupBox {
        id: groupBox
        anchors.fill: parent
        title: "Ball setup"
        Layout.fillWidth: true
        Column {
            spacing: 5
            Layout.fillWidth: true
            TextField {
                horizontalAlignment: TextInput.AlignHCenter
                placeholderText: "pos x = "
            }
            TextField {
                horizontalAlignment: TextInput.AlignHCenter
                placeholderText: "pos y = "
            }
            TextField {
                horizontalAlignment: TextInput.AlignHCenter
                placeholderText: "pos z = "
            }
            TextField {
                horizontalAlignment: TextInput.AlignHCenter
                placeholderText: "vel x = "
            }
            TextField {
                horizontalAlignment: TextInput.AlignHCenter
                placeholderText: "vel y = "
            }
            TextField {
                horizontalAlignment: TextInput.AlignHCenter
                placeholderText: "vel z = "
            }
            TextField {
                horizontalAlignment: TextInput.AlignHCenter
                placeholderText: "radius = "
            }
            Button {
                text: "Apply"

                action: Action {

                    onTriggered: {
                        // proceed received data
                        ballForm.opacity = 0.0
                        ballForm.visible = false
                        root.getFocus()
                    }
                }
            }
        }
    }
}
