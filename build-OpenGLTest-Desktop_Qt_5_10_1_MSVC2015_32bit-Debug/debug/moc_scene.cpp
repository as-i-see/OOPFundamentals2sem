/****************************************************************************
** Meta object code from reading C++ file 'scene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtOpenGLDB/scene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Scene_t {
    QByteArrayData data[16];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Scene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Scene_t qt_meta_stringdata_Scene = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Scene"
QT_MOC_LITERAL(1, 6, 11), // "reloadScene"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "rotateX"
QT_MOC_LITERAL(4, 27, 7), // "rotateY"
QT_MOC_LITERAL(5, 35, 7), // "rotateZ"
QT_MOC_LITERAL(6, 43, 16), // "showXYProjection"
QT_MOC_LITERAL(7, 60, 16), // "showYZProjection"
QT_MOC_LITERAL(8, 77, 16), // "showZXProjection"
QT_MOC_LITERAL(9, 94, 8), // "moveLeft"
QT_MOC_LITERAL(10, 103, 9), // "moveRight"
QT_MOC_LITERAL(11, 113, 8), // "moveDown"
QT_MOC_LITERAL(12, 122, 6), // "moveUp"
QT_MOC_LITERAL(13, 129, 12), // "moveBackward"
QT_MOC_LITERAL(14, 142, 13), // "moveFrontward"
QT_MOC_LITERAL(15, 156, 6) // "update"

    },
    "Scene\0reloadScene\0\0rotateX\0rotateY\0"
    "rotateZ\0showXYProjection\0showYZProjection\0"
    "showZXProjection\0moveLeft\0moveRight\0"
    "moveDown\0moveUp\0moveBackward\0moveFrontward\0"
    "update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    0,   91,    2, 0x0a /* Public */,
      10,    0,   92,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Scene *_t = static_cast<Scene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reloadScene(); break;
        case 1: _t->rotateX(); break;
        case 2: _t->rotateY(); break;
        case 3: _t->rotateZ(); break;
        case 4: _t->showXYProjection(); break;
        case 5: _t->showYZProjection(); break;
        case 6: _t->showZXProjection(); break;
        case 7: _t->moveLeft(); break;
        case 8: _t->moveRight(); break;
        case 9: _t->moveDown(); break;
        case 10: _t->moveUp(); break;
        case 11: _t->moveBackward(); break;
        case 12: _t->moveFrontward(); break;
        case 13: _t->update(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Scene::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_Scene.data,
      qt_meta_data_Scene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Scene.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int Scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
