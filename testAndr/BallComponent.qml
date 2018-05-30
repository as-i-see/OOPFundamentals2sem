import QtQuick 2.1
import Qt3D.Core 2.0
import Qt3D.Animation 2.9
import Qt3D.Extras 2.0
import Qt3D.Input 2.0
import Qt3D.Logic 2.0
import Qt3D.Render 2.0
import QtQuick.Scene3D 2.0

Entity {
    id: sphere
    property Component component
    property SphereMesh mesh: {
        id: sphereMesh
        radius: 20
    }
    property PhongMaterial material: {
        id: material
        ambient: Qt.rgba(1, 0, 0, 1.0);
        diffuse: Qt.rgba( 1, 0, 0, 1.0 )
        specular: Qt.rgba(1, 0, 0, 1.0 )
        shininess: 1.0
    }
    components: []


    signal componentReady(Component component)

    Component.onCompleted: {

    }
}
