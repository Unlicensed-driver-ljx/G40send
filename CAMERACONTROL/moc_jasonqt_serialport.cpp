/****************************************************************************
** Meta object code from reading C++ file 'jasonqt_serialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../QTracker_booster_G4040/IO/jasonqt_serialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jasonqt_serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JasonQt_SerialPort_run_t {
    QByteArrayData data[20];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JasonQt_SerialPort_run_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JasonQt_SerialPort_run_t qt_meta_stringdata_JasonQt_SerialPort_run = {
    {
QT_MOC_LITERAL(0, 0, 22), // "JasonQt_SerialPort_run"
QT_MOC_LITERAL(1, 23, 13), // "controlOpened"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 6), // "isOpen"
QT_MOC_LITERAL(4, 45, 4), // "open"
QT_MOC_LITERAL(5, 50, 8), // "portName"
QT_MOC_LITERAL(6, 59, 8), // "baudRate"
QT_MOC_LITERAL(7, 68, 21), // "QSerialPort::DataBits"
QT_MOC_LITERAL(8, 90, 8), // "dataBits"
QT_MOC_LITERAL(9, 99, 19), // "QSerialPort::Parity"
QT_MOC_LITERAL(10, 119, 6), // "parity"
QT_MOC_LITERAL(11, 126, 21), // "QSerialPort::StopBits"
QT_MOC_LITERAL(12, 148, 8), // "stopBits"
QT_MOC_LITERAL(13, 157, 5), // "close"
QT_MOC_LITERAL(14, 163, 4), // "send"
QT_MOC_LITERAL(15, 168, 4), // "data"
QT_MOC_LITERAL(16, 173, 8), // "accepted"
QT_MOC_LITERAL(17, 182, 9), // "accepted0"
QT_MOC_LITERAL(18, 192, 5), // "error"
QT_MOC_LITERAL(19, 198, 28) // "QSerialPort::SerialPortError"

    },
    "JasonQt_SerialPort_run\0controlOpened\0"
    "\0isOpen\0open\0portName\0baudRate\0"
    "QSerialPort::DataBits\0dataBits\0"
    "QSerialPort::Parity\0parity\0"
    "QSerialPort::StopBits\0stopBits\0close\0"
    "send\0data\0accepted\0accepted0\0error\0"
    "QSerialPort::SerialPortError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JasonQt_SerialPort_run[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    5,   52,    2, 0x0a /* Public */,
      13,    0,   63,    2, 0x0a /* Public */,
      14,    1,   64,    2, 0x0a /* Public */,
      16,    0,   67,    2, 0x08 /* Private */,
      17,    0,   68,    2, 0x08 /* Private */,
      18,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11,    5,    6,    8,   10,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   18,

       0        // eod
};

void JasonQt_SerialPort_run::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JasonQt_SerialPort_run *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->controlOpened((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QSerialPort::DataBits(*)>(_a[3])),(*reinterpret_cast< const QSerialPort::Parity(*)>(_a[4])),(*reinterpret_cast< const QSerialPort::StopBits(*)>(_a[5]))); break;
        case 2: _t->close(); break;
        case 3: _t->send((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->accepted(); break;
        case 5: _t->accepted0(); break;
        case 6: _t->error((*reinterpret_cast< const QSerialPort::SerialPortError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (JasonQt_SerialPort_run::*)(const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JasonQt_SerialPort_run::controlOpened)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JasonQt_SerialPort_run::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_JasonQt_SerialPort_run.data,
    qt_meta_data_JasonQt_SerialPort_run,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *JasonQt_SerialPort_run::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JasonQt_SerialPort_run::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JasonQt_SerialPort_run.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int JasonQt_SerialPort_run::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void JasonQt_SerialPort_run::controlOpened(const bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_JasonQt_SerialPort_t {
    QByteArrayData data[23];
    char stringdata0[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JasonQt_SerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JasonQt_SerialPort_t qt_meta_stringdata_JasonQt_SerialPort = {
    {
QT_MOC_LITERAL(0, 0, 18), // "JasonQt_SerialPort"
QT_MOC_LITERAL(1, 19, 8), // "accepted"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "data"
QT_MOC_LITERAL(4, 34, 9), // "accepted0"
QT_MOC_LITERAL(5, 44, 5), // "error"
QT_MOC_LITERAL(6, 50, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(7, 79, 11), // "controlOpen"
QT_MOC_LITERAL(8, 91, 8), // "portName"
QT_MOC_LITERAL(9, 100, 8), // "baudRate"
QT_MOC_LITERAL(10, 109, 21), // "QSerialPort::DataBits"
QT_MOC_LITERAL(11, 131, 8), // "dataBits"
QT_MOC_LITERAL(12, 140, 19), // "QSerialPort::Parity"
QT_MOC_LITERAL(13, 160, 6), // "parity"
QT_MOC_LITERAL(14, 167, 21), // "QSerialPort::StopBits"
QT_MOC_LITERAL(15, 189, 8), // "stopBits"
QT_MOC_LITERAL(16, 198, 12), // "controlClose"
QT_MOC_LITERAL(17, 211, 11), // "controlSend"
QT_MOC_LITERAL(18, 223, 4), // "open"
QT_MOC_LITERAL(19, 228, 5), // "close"
QT_MOC_LITERAL(20, 234, 4), // "send"
QT_MOC_LITERAL(21, 239, 11), // "const char*"
QT_MOC_LITERAL(22, 251, 4) // "size"

    },
    "JasonQt_SerialPort\0accepted\0\0data\0"
    "accepted0\0error\0QSerialPort::SerialPortError\0"
    "controlOpen\0portName\0baudRate\0"
    "QSerialPort::DataBits\0dataBits\0"
    "QSerialPort::Parity\0parity\0"
    "QSerialPort::StopBits\0stopBits\0"
    "controlClose\0controlSend\0open\0close\0"
    "send\0const char*\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JasonQt_SerialPort[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    1,   90,    2, 0x06 /* Public */,
       7,    5,   93,    2, 0x06 /* Public */,
      16,    0,  104,    2, 0x06 /* Public */,
      17,    1,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    5,  108,    2, 0x0a /* Public */,
      18,    4,  119,    2, 0x2a /* Public | MethodCloned */,
      18,    3,  128,    2, 0x2a /* Public | MethodCloned */,
      18,    2,  135,    2, 0x2a /* Public | MethodCloned */,
      19,    0,  140,    2, 0x0a /* Public */,
      20,    1,  141,    2, 0x0a /* Public */,
      20,    2,  144,    2, 0x0a /* Public */,
      20,    1,  149,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 6,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 12, 0x80000000 | 14,    8,    9,   11,   13,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 12, 0x80000000 | 14,    8,    9,   11,   13,   15,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 12,    8,    9,   11,   13,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int, 0x80000000 | 10,    8,    9,   11,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Int,    3,   22,
    QMetaType::Void, 0x80000000 | 21,    3,

       0        // eod
};

void JasonQt_SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JasonQt_SerialPort *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->accepted((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->accepted0((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->error((*reinterpret_cast< const QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 3: _t->controlOpen((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QSerialPort::DataBits(*)>(_a[3])),(*reinterpret_cast< const QSerialPort::Parity(*)>(_a[4])),(*reinterpret_cast< QSerialPort::StopBits(*)>(_a[5]))); break;
        case 4: _t->controlClose(); break;
        case 5: _t->controlSend((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QSerialPort::DataBits(*)>(_a[3])),(*reinterpret_cast< const QSerialPort::Parity(*)>(_a[4])),(*reinterpret_cast< const QSerialPort::StopBits(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QSerialPort::DataBits(*)>(_a[3])),(*reinterpret_cast< const QSerialPort::Parity(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QSerialPort::DataBits(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->close(); break;
        case 11: _t->send((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 12: _t->send((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->send((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (JasonQt_SerialPort::*)(const QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JasonQt_SerialPort::accepted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (JasonQt_SerialPort::*)(const QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JasonQt_SerialPort::accepted0)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (JasonQt_SerialPort::*)(const QSerialPort::SerialPortError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JasonQt_SerialPort::error)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (JasonQt_SerialPort::*)(const QString , const int , const QSerialPort::DataBits , const QSerialPort::Parity , QSerialPort::StopBits );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JasonQt_SerialPort::controlOpen)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (JasonQt_SerialPort::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JasonQt_SerialPort::controlClose)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (JasonQt_SerialPort::*)(const QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JasonQt_SerialPort::controlSend)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JasonQt_SerialPort::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_JasonQt_SerialPort.data,
    qt_meta_data_JasonQt_SerialPort,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *JasonQt_SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JasonQt_SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JasonQt_SerialPort.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int JasonQt_SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void JasonQt_SerialPort::accepted(const QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void JasonQt_SerialPort::accepted0(const QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void JasonQt_SerialPort::error(const QSerialPort::SerialPortError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void JasonQt_SerialPort::controlOpen(const QString _t1, const int _t2, const QSerialPort::DataBits _t3, const QSerialPort::Parity _t4, QSerialPort::StopBits _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void JasonQt_SerialPort::controlClose()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void JasonQt_SerialPort::controlSend(const QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
