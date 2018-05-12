import QtQuick 2.1
import Qt3D.Core 2.0
import Qt3D.Animation 2.9
import Qt3D.Extras 2.0
import Qt3D.Input 2.0
import Qt3D.Logic 2.0
import Qt3D.Render 2.0
import QtQuick.Scene3D 2.0

Entity {
    id: cage;
    PhongMaterial {
        id: edgeMaterial
        ambient: Qt.rgba(0, 0, 0, 1.0);
        diffuse: Qt.rgba( 0, 0, 0, 1.0 )
        specular: Qt.rgba(0, 0, 0, 1.0 )
        shininess: 1.0
    }

    CylinderMesh {
        id: cylinderMesh
        length: 100
        radius: 0.5
    }

    Transform {
        id: edgeTransform1
        translation: Qt.vector3d(-50, 0, 50);
    }

    Entity {
        id: edgeEntity1
        components: [ cylinderMesh, edgeTransform1, edgeMaterial ]
    }

    Transform {
        id: edgeTransform2
        translation: Qt.vector3d(-50, 0, -50);
    }

    Entity {
        id: edgeEntity2
        components: [ cylinderMesh, edgeTransform2, edgeMaterial ]
    }

    Transform {
        id: edgeTransform3
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 90)
        translation: Qt.vector3d(-50, 50, 0)
    }

    Entity {
        id: edgeEntity3
        components: [ cylinderMesh, edgeTransform3, edgeMaterial ]
    }

    Transform {
        id: edgeTransform4
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 90)
        translation: Qt.vector3d(-50, -50, 0)
    }

    Entity {
        id: edgeEntity4
        components: [ cylinderMesh, edgeTransform4, edgeMaterial ]
    }

    Transform {
        id: edgeTransform5
        rotation: fromAxisAndAngle(Qt.vector3d(0, 0, 1), 90)
        translation: Qt.vector3d(0, -50, 50)
    }

    Entity {
        id: edgeEntity5
        components: [ cylinderMesh, edgeTransform5, edgeMaterial ]
    }

    Transform {
        id: edgeTransform6
        rotation: fromAxisAndAngle(Qt.vector3d(0, 0, 1), 90)
        translation: Qt.vector3d(0, -50, -50)
    }

    Entity {
        id: edgeEntity6
        components: [ cylinderMesh, edgeTransform6, edgeMaterial ]
    }
    Transform {
        id: edgeTransform7
        rotation: fromAxisAndAngle(Qt.vector3d(0, 0, 1), 90)
        translation: Qt.vector3d(0, 50, 50)
    }

    Entity {
        id: edgeEntity7
        components: [ cylinderMesh, edgeTransform7, edgeMaterial ]
    }
    Transform {
        id: edgeTransform8
        rotation: fromAxisAndAngle(Qt.vector3d(0, 0, 1), 90)
        translation: Qt.vector3d(0, 50, -50)
    }

    Entity {
        id: edgeEntity8
        components: [ cylinderMesh, edgeTransform8, edgeMaterial ]
    }

    Transform {
        id: edgeTransform9
        translation: Qt.vector3d(50, 0, -50)
    }

    Entity {
        id: edgeEntity9
        components: [ cylinderMesh, edgeTransform9, edgeMaterial ]
    }
    Transform {
        id: edgeTransform10
        translation: Qt.vector3d(50, 0, 50)
    }

    Entity {
        id: edgeEntity10
        components: [ cylinderMesh, edgeTransform10, edgeMaterial ]
    }
    Transform {
        id: edgeTransform11
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 90)
        translation: Qt.vector3d(50, 50, 0)
    }

    Entity {
        id: edgeEntity11
        components: [ cylinderMesh, edgeTransform11, edgeMaterial ]
    }
    Transform {
        id: edgeTransform12
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 90)
        translation: Qt.vector3d(50, -50, 0)
    }

    Entity {
        id: edgeEntity12
        components: [ cylinderMesh, edgeTransform12, edgeMaterial ]
    }
}


