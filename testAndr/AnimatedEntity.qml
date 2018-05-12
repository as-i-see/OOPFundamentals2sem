import QtQuick 2.1
import Qt3D.Core 2.0
import Qt3D.Animation 2.9
import Qt3D.Extras 2.0
import Qt3D.Input 2.0
import Qt3D.Logic 2.0
import Qt3D.Render 2.0
import QtQuick.Scene3D 2.0


Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 60
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 125.0, 0.0, 0.0 )
        upVector: Qt.vector3d( 0.0, 0.0, 1.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    FirstPersonCameraController { camera: camera }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera                
                clearColor: "#e1e6e8"

            }
        },
        InputSettings { }
    ]

    PhongMaterial {
        id: material
        ambient: Qt.rgba(1, 0, 0, 1.0);
        diffuse: Qt.rgba( 1, 0, 0, 1.0 )
        specular: Qt.rgba(1, 0, 0, 1.0 )
        shininess: 1.0
    }

    SphereMesh {
        id: sphereMesh
        radius: 20
    }

    Entity {
        id: sphereEntity
        components: [ sphereMesh, material ]
    }

    Cage {}
}
