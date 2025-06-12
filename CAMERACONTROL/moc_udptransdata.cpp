/****************************************************************************
** Meta object code from reading C++ file 'udptransdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../QTracker_booster_G4040/IO/udptransdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udptransdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UDPTransData_t {
    QByteArrayData data[27];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UDPTransData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UDPTransData_t qt_meta_stringdata_UDPTransData = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UDPTransData"
QT_MOC_LITERAL(1, 13, 12), // "moveT210Step"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9), // "direction"
QT_MOC_LITERAL(4, 37, 4), // "step"
QT_MOC_LITERAL(5, 42, 12), // "moveT2102Pos"
QT_MOC_LITERAL(6, 55, 6), // "aAngle"
QT_MOC_LITERAL(7, 62, 6), // "eAngle"
QT_MOC_LITERAL(8, 69, 14), // "changeT210mode"
QT_MOC_LITERAL(9, 84, 11), // "controlMode"
QT_MOC_LITERAL(10, 96, 12), // "XXTFocusStep"
QT_MOC_LITERAL(11, 109, 13), // "BackOrForward"
QT_MOC_LITERAL(12, 123, 7), // "XXTZoom"
QT_MOC_LITERAL(13, 131, 7), // "zoomPos"
QT_MOC_LITERAL(14, 139, 11), // "XXTZoomStep"
QT_MOC_LITERAL(15, 151, 13), // "backOrForward"
QT_MOC_LITERAL(16, 165, 23), // "changeDspObjectProperty"
QT_MOC_LITERAL(17, 189, 14), // "objectProperty"
QT_MOC_LITERAL(18, 204, 14), // "laserOpenClose"
QT_MOC_LITERAL(19, 219, 9), // "openClose"
QT_MOC_LITERAL(20, 229, 12), // "laserCurrent"
QT_MOC_LITERAL(21, 242, 7), // "current"
QT_MOC_LITERAL(22, 250, 13), // "laserMotorPos"
QT_MOC_LITERAL(23, 264, 8), // "motorPos"
QT_MOC_LITERAL(24, 273, 11), // "ReceiveText"
QT_MOC_LITERAL(25, 285, 14), // "sendOurMessage"
QT_MOC_LITERAL(26, 300, 11) // "initUDPPort"

    },
    "UDPTransData\0moveT210Step\0\0direction\0"
    "step\0moveT2102Pos\0aAngle\0eAngle\0"
    "changeT210mode\0controlMode\0XXTFocusStep\0"
    "BackOrForward\0XXTZoom\0zoomPos\0XXTZoomStep\0"
    "backOrForward\0changeDspObjectProperty\0"
    "objectProperty\0laserOpenClose\0openClose\0"
    "laserCurrent\0current\0laserMotorPos\0"
    "motorPos\0ReceiveText\0sendOurMessage\0"
    "initUDPPort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UDPTransData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       5,    2,   84,    2, 0x06 /* Public */,
       8,    1,   89,    2, 0x06 /* Public */,
      10,    1,   92,    2, 0x06 /* Public */,
      12,    1,   95,    2, 0x06 /* Public */,
      14,    1,   98,    2, 0x06 /* Public */,
      16,    1,  101,    2, 0x06 /* Public */,
      18,    1,  104,    2, 0x06 /* Public */,
      20,    1,  107,    2, 0x06 /* Public */,
      22,    1,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    0,  113,    2, 0x0a /* Public */,
      25,    0,  114,    2, 0x0a /* Public */,
      26,    0,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   23,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,

       0        // eod
};

void UDPTransData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UDPTransData *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->moveT210Step((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->moveT2102Pos((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 2: _t->changeT210mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->XXTFocusStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->XXTZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->XXTZoomStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->changeDspObjectProperty((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->laserOpenClose((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->laserCurrent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->laserMotorPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->ReceiveText(); break;
        case 11: _t->sendOurMessage(); break;
        case 12: { bool _r = _t->initUDPPort();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UDPTransData::*)(int , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::moveT210Step)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::moveT2102Pos)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::changeT210mode)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::XXTFocusStep)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::XXTZoom)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::XXTZoomStep)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::changeDspObjectProperty)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::laserOpenClose)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::laserCurrent)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (UDPTransData::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPTransData::laserMotorPos)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UDPTransData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_UDPTransData.data,
    qt_meta_data_UDPTransData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UDPTransData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UDPTransData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UDPTransData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UDPTransData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void UDPTransData::moveT210Step(int _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UDPTransData::moveT2102Pos(float _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UDPTransData::changeT210mode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UDPTransData::XXTFocusStep(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UDPTransData::XXTZoom(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UDPTransData::XXTZoomStep(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void UDPTransData::changeDspObjectProperty(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void UDPTransData::laserOpenClose(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void UDPTransData::laserCurrent(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void UDPTransData::laserMotorPos(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
