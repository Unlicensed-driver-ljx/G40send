/****************************************************************************
** Meta object code from reading C++ file 'comserialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../QTracker_booster_G4040/IO/comserialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comserialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_comserialport_t {
    QByteArrayData data[20];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_comserialport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_comserialport_t qt_meta_stringdata_comserialport = {
    {
QT_MOC_LITERAL(0, 0, 13), // "comserialport"
QT_MOC_LITERAL(1, 14, 8), // "readdata"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "data"
QT_MOC_LITERAL(4, 29, 8), // "ReadData"
QT_MOC_LITERAL(5, 38, 17), // "readCameraControl"
QT_MOC_LITERAL(6, 56, 20), // "ByteArrayToHexString"
QT_MOC_LITERAL(7, 77, 9), // "GetCrc_16"
QT_MOC_LITERAL(8, 87, 5), // "char*"
QT_MOC_LITERAL(9, 93, 5), // "pData"
QT_MOC_LITERAL(10, 99, 7), // "nLength"
QT_MOC_LITERAL(11, 107, 4), // "init"
QT_MOC_LITERAL(12, 112, 21), // "const unsigned short*"
QT_MOC_LITERAL(13, 134, 6), // "ptable"
QT_MOC_LITERAL(14, 141, 15), // "CRC_GetModbus16"
QT_MOC_LITERAL(15, 157, 8), // "uint16_t"
QT_MOC_LITERAL(16, 166, 5), // "pdata"
QT_MOC_LITERAL(17, 172, 3), // "len"
QT_MOC_LITERAL(18, 176, 14), // "QList<uint8_t>"
QT_MOC_LITERAL(19, 191, 15) // "const uint16_t*"

    },
    "comserialport\0readdata\0\0data\0ReadData\0"
    "readCameraControl\0ByteArrayToHexString\0"
    "GetCrc_16\0char*\0pData\0nLength\0init\0"
    "const unsigned short*\0ptable\0"
    "CRC_GetModbus16\0uint16_t\0pdata\0len\0"
    "QList<uint8_t>\0const uint16_t*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_comserialport[] = {

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
       5,    0,   60,    2, 0x0a /* Public */,
       6,    1,   61,    2, 0x0a /* Public */,
       7,    4,   64,    2, 0x0a /* Public */,
      14,    2,   73,    2, 0x0a /* Public */,
       7,    4,   78,    2, 0x0a /* Public */,
      14,    2,   87,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QByteArray,    3,
    QMetaType::Bool, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QByteArray,    3,
    QMetaType::UShort, 0x80000000 | 8, QMetaType::Int, QMetaType::UShort, 0x80000000 | 12,    9,   10,   11,   13,
    0x80000000 | 15, 0x80000000 | 8, QMetaType::Int,   16,   17,
    0x80000000 | 15, 0x80000000 | 18, QMetaType::Int, 0x80000000 | 15, 0x80000000 | 19,    9,   10,   11,   13,
    0x80000000 | 15, 0x80000000 | 18, QMetaType::Int,   16,   17,

       0        // eod
};

void comserialport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<comserialport *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { bool _r = _t->readdata((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->ReadData((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->readCameraControl(); break;
        case 3: { QString _r = _t->ByteArrayToHexString((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { unsigned short _r = _t->GetCrc_16((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< unsigned short(*)>(_a[3])),(*reinterpret_cast< const unsigned short*(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< unsigned short*>(_a[0]) = std::move(_r); }  break;
        case 5: { uint16_t _r = _t->CRC_GetModbus16((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = std::move(_r); }  break;
        case 6: { uint16_t _r = _t->GetCrc_16((*reinterpret_cast< QList<uint8_t>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< uint16_t(*)>(_a[3])),(*reinterpret_cast< const uint16_t*(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = std::move(_r); }  break;
        case 7: { uint16_t _r = _t->CRC_GetModbus16((*reinterpret_cast< QList<uint8_t>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject comserialport::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_comserialport.data,
    qt_meta_data_comserialport,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *comserialport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *comserialport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_comserialport.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int comserialport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
