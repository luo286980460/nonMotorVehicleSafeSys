/****************************************************************************
** Meta object code from reading C++ file 'novacontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../novacontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'novacontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NovaController_t {
    QByteArrayData data[16];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NovaController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NovaController_t qt_meta_stringdata_NovaController = {
    {
QT_MOC_LITERAL(0, 0, 14), // "NovaController"
QT_MOC_LITERAL(1, 15, 7), // "showMsg"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "msg"
QT_MOC_LITERAL(4, 28, 16), // "signalInitWorker"
QT_MOC_LITERAL(5, 45, 16), // "signalIllegalAct"
QT_MOC_LITERAL(6, 62, 18), // "signalPlayProgram1"
QT_MOC_LITERAL(7, 81, 8), // "fontSize"
QT_MOC_LITERAL(8, 90, 7), // "content"
QT_MOC_LITERAL(9, 98, 10), // "audioTimes"
QT_MOC_LITERAL(10, 109, 12), // "voiceContent"
QT_MOC_LITERAL(11, 122, 11), // "audioSwitch"
QT_MOC_LITERAL(12, 134, 11), // "audiovolume"
QT_MOC_LITERAL(13, 146, 18), // "signalPlayProgram2"
QT_MOC_LITERAL(14, 165, 6), // "base64"
QT_MOC_LITERAL(15, 172, 18) // "signalPlayProgram3"

    },
    "NovaController\0showMsg\0\0msg\0"
    "signalInitWorker\0signalIllegalAct\0"
    "signalPlayProgram1\0fontSize\0content\0"
    "audioTimes\0voiceContent\0audioSwitch\0"
    "audiovolume\0signalPlayProgram2\0base64\0"
    "signalPlayProgram3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NovaController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,
       5,    0,   48,    2, 0x06 /* Public */,
       6,    6,   49,    2, 0x06 /* Public */,
      13,    1,   62,    2, 0x06 /* Public */,
      15,    7,   65,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::QString,    7,    8,    9,   10,   11,   12,   14,

       0        // eod
};

void NovaController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NovaController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalInitWorker(); break;
        case 2: _t->signalIllegalAct(); break;
        case 3: _t->signalPlayProgram1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 4: _t->signalPlayProgram2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->signalPlayProgram3((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NovaController::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NovaController::showMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NovaController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NovaController::signalInitWorker)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NovaController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NovaController::signalIllegalAct)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NovaController::*)(int , QString , int , QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NovaController::signalPlayProgram1)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NovaController::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NovaController::signalPlayProgram2)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NovaController::*)(int , QString , int , QString , int , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NovaController::signalPlayProgram3)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NovaController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NovaController.data,
    qt_meta_data_NovaController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NovaController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NovaController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NovaController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NovaController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NovaController::showMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NovaController::signalInitWorker()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NovaController::signalIllegalAct()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void NovaController::signalPlayProgram1(int _t1, QString _t2, int _t3, QString _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NovaController::signalPlayProgram2(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NovaController::signalPlayProgram3(int _t1, QString _t2, int _t3, QString _t4, int _t5, int _t6, QString _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
