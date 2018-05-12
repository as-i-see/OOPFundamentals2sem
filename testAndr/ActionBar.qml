import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.1

ToolBar {
    id: root
    height: 50

    signal menuClicked() // A signal that reports a click on the menu button

    Rectangle { // bar
        anchors.fill: parent
        color: "white"

        Image { // icon
            id: ico
            height: root.height
            width: root.height
            anchors {
                left: parent.left
                leftMargin: 10
                top: parent.top
            }
            source: "qrc:/images/logo.jpg"
        }


        Text { // label
            anchors {
                verticalCenter: parent.verticalCenter
                left: ico.right
                leftMargin: 5
            }

            text: qsTr("Крепкие шары")
            font.pixelSize: 24
            color: "black"
        }

        Image {
            id: menuIcon
            height: root.height - 15
            width: root.height - 15
            anchors {
                right: parent.right
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/images/menu.png"
            MouseArea {
                id: menuArea
                anchors.fill: parent
                onClicked: root.menuClicked()
            }
        }
    }
}
