/****************************************************************************
** Meta object code from reading C++ file 'novacontrollerworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../novacontrollerworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'novacontrollerworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NovaControllerWorker_t {
    QByteArrayData data[16];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NovaControllerWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NovaControllerWorker_t qt_meta_stringdata_NovaControllerWorker = {
    {
QT_MOC_LITERAL(0, 0, 20), // "NovaControllerWorker"
QT_MOC_LITERAL(1, 21, 7), // "showMsg"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "msg"
QT_MOC_LITERAL(4, 34, 8), // "slotInit"
QT_MOC_LITERAL(5, 43, 14), // "slotIllegalAct"
QT_MOC_LITERAL(6, 58, 16), // "slotPlayProgram1"
QT_MOC_LITERAL(7, 75, 8), // "fontSize"
QT_MOC_LITERAL(8, 84, 7), // "content"
QT_MOC_LITERAL(9, 92, 10), // "audioTimes"
QT_MOC_LITERAL(10, 103, 12), // "voiceContent"
QT_MOC_LITERAL(11, 116, 11), // "audioSwitch"
QT_MOC_LITERAL(12, 128, 11), // "audiovolume"
QT_MOC_LITERAL(13, 140, 16), // "slotPlayProgram2"
QT_MOC_LITERAL(14, 157, 6), // "base64"
QT_MOC_LITERAL(15, 164, 16) // "slotPlayProgram3"

    },
    "NovaControllerWorker\0showMsg\0\0msg\0"
    "slotInit\0slotIllegalAct\0slotPlayProgram1\0"
    "fontSize\0content\0audioTimes\0voiceContent\0"
    "audioSwitch\0audiovolume\0slotPlayProgram2\0"
    "base64\0slotPlayProgram3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NovaControllerWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   47,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    6,   49,    2, 0x0a /* Public */,
      13,    1,   62,    2, 0x0a /* Public */,
      15,    7,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::QString,    7,    8,    9,   10,   11,   12,   14,

       0        // eod
};

void NovaControllerWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NovaControllerWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotInit(); break;
        case 2: _t->slotIllegalAct(); break;
        case 3: _t->slotPlayProgram1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 4: _t->slotPlayProgram2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slotPlayProgram3((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NovaControllerWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NovaControllerWorker::showMsg)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NovaControllerWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NovaControllerWorker.data,
    qt_meta_data_NovaControllerWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NovaControllerWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NovaControllerWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NovaControllerWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NovaControllerWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void NovaControllerWorker::showMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
