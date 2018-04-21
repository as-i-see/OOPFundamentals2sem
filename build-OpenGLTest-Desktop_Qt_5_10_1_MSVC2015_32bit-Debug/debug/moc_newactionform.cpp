/****************************************************************************
** Meta object code from reading C++ file 'newactionform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtOpenGLDB/newactionform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newactionform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NewActionForm_t {
    QByteArrayData data[6];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewActionForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewActionForm_t qt_meta_stringdata_NewActionForm = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NewActionForm"
QT_MOC_LITERAL(1, 14, 17), // "creationCompleted"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 32), // "std::pair<std::vector<Cube>,int>"
QT_MOC_LITERAL(4, 66, 12), // "newCubeReady"
QT_MOC_LITERAL(5, 79, 4) // "Cube"

    },
    "NewActionForm\0creationCompleted\0\0"
    "std::pair<std::vector<Cube>,int>\0"
    "newCubeReady\0Cube"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewActionForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       1,    0,   32,    2, 0x0a /* Public */,
       4,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void NewActionForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewActionForm *_t = static_cast<NewActionForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->creationCompleted((*reinterpret_cast< std::pair<std::vector<Cube>,int>(*)>(_a[1]))); break;
        case 1: _t->creationCompleted(); break;
        case 2: _t->newCubeReady((*reinterpret_cast< Cube(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (NewActionForm::*_t)(std::pair<std::vector<Cube>,int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NewActionForm::creationCompleted)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NewActionForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NewActionForm.data,
      qt_meta_data_NewActionForm,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NewActionForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewActionForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NewActionForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int NewActionForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void NewActionForm::creationCompleted(std::pair<std::vector<Cube>,int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
