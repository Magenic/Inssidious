/****************************************************************************
** Meta object code from reading C++ file 'start.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Widgets/start.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'start.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Start_t {
    QByteArrayData data[10];
    char stringdata[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Start_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Start_t qt_meta_stringdata_Start = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Start"
QT_MOC_LITERAL(1, 6, 9), // "startCore"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 11), // "networkName"
QT_MOC_LITERAL(4, 29, 15), // "networkPassword"
QT_MOC_LITERAL(5, 45, 14), // "networkAdapter"
QT_MOC_LITERAL(6, 60, 14), // "onUpdateStatus"
QT_MOC_LITERAL(7, 75, 16), // "newStatusMessage"
QT_MOC_LITERAL(8, 92, 5), // "error"
QT_MOC_LITERAL(9, 98, 20) // "onStartButtonClicked"

    },
    "Start\0startCore\0\0networkName\0"
    "networkPassword\0networkAdapter\0"
    "onUpdateStatus\0newStatusMessage\0error\0"
    "onStartButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Start[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   41,    2, 0x0a /* Public */,
       6,    1,   46,    2, 0x2a /* Public | MethodCloned */,
       9,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    7,    8,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

       0        // eod
};

void Start::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Start *_t = static_cast<Start *>(_o);
        switch (_id) {
        case 0: _t->startCore((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->onUpdateStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->onUpdateStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onStartButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Start::*_t)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Start::startCore)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Start::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Start.data,
      qt_meta_data_Start,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Start::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Start::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Start.stringdata))
        return static_cast<void*>(const_cast< Start*>(this));
    return QWidget::qt_metacast(_clname);
}

int Start::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Start::startCore(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
