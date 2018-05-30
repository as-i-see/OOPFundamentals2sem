import QtQuick 2.0
import Qt3D.Core 2.0
import Qt3D.Animation 2.9
import Qt3D.Extras 2.0
import Qt3D.Input 2.0
import Qt3D.Logic 2.0
import Qt3D.Render 2.0
import QtQuick.Scene3D 2.0

Rectangle {
    id: scene
    anchors.fill: parent
    visible: true
    color: "#f7f7fc"

    Connections {
        target: root
        onLooseFocus: {
            scene.visible = false
        }
        onGetFocus: scene.visible = true
    }

    Scene3D {
        id: scene3d
        anchors.fill: parent
        focus: true
        aspects: ["input", "logic"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
        AnimatedEntity {}

    }

}


