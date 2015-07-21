/****************************************************************************
** Meta object code from reading C++ file 'core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Core_t {
    QByteArrayData data[16];
    char stringdata[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core_t qt_meta_stringdata_Core = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Core"
QT_MOC_LITERAL(1, 5, 12), // "updateStatus"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 13), // "statusMessage"
QT_MOC_LITERAL(4, 33, 5), // "error"
QT_MOC_LITERAL(5, 39, 7), // "started"
QT_MOC_LITERAL(6, 47, 15), // "deviceConnected"
QT_MOC_LITERAL(7, 63, 18), // "deviceDisconnected"
QT_MOC_LITERAL(8, 82, 11), // "onCoreStart"
QT_MOC_LITERAL(9, 94, 11), // "networkName"
QT_MOC_LITERAL(10, 106, 15), // "networkPassword"
QT_MOC_LITERAL(11, 122, 14), // "networkAdapter"
QT_MOC_LITERAL(12, 137, 22), // "onHostedNetworkMessage"
QT_MOC_LITERAL(13, 160, 7), // "message"
QT_MOC_LITERAL(14, 168, 19), // "HostedNetworkReason"
QT_MOC_LITERAL(15, 188, 6) // "reason"

    },
    "Core\0updateStatus\0\0statusMessage\0error\0"
    "started\0deviceConnected\0deviceDisconnected\0"
    "onCoreStart\0networkName\0networkPassword\0"
    "networkAdapter\0onHostedNetworkMessage\0"
    "message\0HostedNetworkReason\0reason"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       1,    1,   54,    2, 0x26 /* Public | MethodCloned */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    1,   58,    2, 0x06 /* Public */,
       7,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    3,   64,    2, 0x0a /* Public */,
      12,    2,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    9,   10,   11,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 14,   13,   15,

       0        // eod
};

void Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Core *_t = static_cast<Core *>(_o);
        switch (_id) {
        case 0: _t->updateStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->updateStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->started(); break;
        case 3: _t->deviceConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->deviceDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onCoreStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: _t->onHostedNetworkMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< HostedNetworkReason(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Core::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Core::updateStatus)) {
                *result = 0;
            }
        }
        {
            typedef void (Core::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Core::started)) {
                *result = 2;
            }
        }
        {
            typedef void (Core::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Core::deviceConnected)) {
                *result = 3;
            }
        }
        {
            typedef void (Core::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Core::deviceDisconnected)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Core::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Core.data,
      qt_meta_data_Core,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Core.stringdata))
        return static_cast<void*>(const_cast< Core*>(this));
    return QThread::qt_metacast(_clname);
}

int Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void Core::updateStatus(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void Core::started()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Core::deviceConnected(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Core::deviceDisconnected(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
