/****************************************************************************
** Meta object code from reading C++ file 'onlinetunedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../QTracker_booster_G4040/UI/onlinetunedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'onlinetunedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OnlineTuneDialog_t {
    QByteArrayData data[13];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OnlineTuneDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OnlineTuneDialog_t qt_meta_stringdata_OnlineTuneDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "OnlineTuneDialog"
QT_MOC_LITERAL(1, 17, 10), // "Delay_MSec"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "msec"
QT_MOC_LITERAL(4, 34, 23), // "CameraSetCameraLinkMode"
QT_MOC_LITERAL(5, 58, 5), // "state"
QT_MOC_LITERAL(6, 64, 20), // "CameraSetImageFormat"
QT_MOC_LITERAL(7, 85, 17), // "CameraSetImageBit"
QT_MOC_LITERAL(8, 103, 3), // "val"
QT_MOC_LITERAL(9, 107, 17), // "CameraSetImageTap"
QT_MOC_LITERAL(10, 125, 17), // "onC640CameraState"
QT_MOC_LITERAL(11, 143, 18), // "on_btnSend_clicked"
QT_MOC_LITERAL(12, 162, 21) // "on_btnReceive_clicked"

    },
    "OnlineTuneDialog\0Delay_MSec\0\0msec\0"
    "CameraSetCameraLinkMode\0state\0"
    "CameraSetImageFormat\0CameraSetImageBit\0"
    "val\0CameraSetImageTap\0onC640CameraState\0"
    "on_btnSend_clicked\0on_btnReceive_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OnlineTuneDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    1,   57,    2, 0x0a /* Public */,
       6,    1,   60,    2, 0x0a /* Public */,
       7,    1,   63,    2, 0x0a /* Public */,
       9,    1,   66,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x08 /* Private */,
      12,    0,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OnlineTuneDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OnlineTuneDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Delay_MSec((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->CameraSetCameraLinkMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->CameraSetImageFormat((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->CameraSetImageBit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->CameraSetImageTap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onC640CameraState(); break;
        case 6: _t->on_btnSend_clicked(); break;
        case 7: _t->on_btnReceive_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OnlineTuneDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_OnlineTuneDialog.data,
    qt_meta_data_OnlineTuneDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OnlineTuneDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OnlineTuneDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OnlineTuneDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int OnlineTuneDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
