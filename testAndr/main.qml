import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Window 2.10
import QtQuick.Controls.Material 2.1
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Лабораторная работа №1")

    header: ActionBar {
        onMenuClicked: actionBarMenu.open() // Open the menu

        Menu {
            id: actionBarMenu
            // With an indication of the location so that Menu pops up in the same place as in the version with Java
            x: root.width
            y: 50
            width: 240
            Action {
                text: qsTr("Load a clean scene")
            }
            Action {
                text: qsTr("Add a new ball to the scene")
                onTriggered: {
                    groupBox.visible = true
                    gridLayout.visible = true
                }

            }
        }

        GroupBox {
            id: groupBox
            title: "Ball setup"
            visible: false
            GridLayout {
                id: gridLayout
                rows: 8
                visible: false
                flow: GridLayout.TopToBottom
                anchors.fill: parent
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
                    action: {
                        groupBox.visible = false
                        gridLayout.visible = false
                    }
                }
            }
        }

    }

    Scene {

    }

}
