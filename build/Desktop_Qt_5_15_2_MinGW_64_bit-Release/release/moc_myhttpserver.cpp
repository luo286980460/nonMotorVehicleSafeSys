/****************************************************************************
** Meta object code from reading C++ file 'myhttpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../myhttpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myhttpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyHttpServer_t {
    QByteArrayData data[13];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyHttpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyHttpServer_t qt_meta_stringdata_MyHttpServer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyHttpServer"
QT_MOC_LITERAL(1, 13, 11), // "signalStart"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 18), // "signalPlayProgram1"
QT_MOC_LITERAL(4, 45, 8), // "fontSize"
QT_MOC_LITERAL(5, 54, 7), // "content"
QT_MOC_LITERAL(6, 62, 10), // "audioTimes"
QT_MOC_LITERAL(7, 73, 12), // "voiceContent"
QT_MOC_LITERAL(8, 86, 11), // "audioSwitch"
QT_MOC_LITERAL(9, 98, 11), // "audiovolume"
QT_MOC_LITERAL(10, 110, 18), // "signalPlayProgram2"
QT_MOC_LITERAL(11, 129, 6), // "base64"
QT_MOC_LITERAL(12, 136, 18) // "signalPlayProgram3"

    },
    "MyHttpServer\0signalStart\0\0signalPlayProgram1\0"
    "fontSize\0content\0audioTimes\0voiceContent\0"
    "audioSwitch\0audiovolume\0signalPlayProgram2\0"
    "base64\0signalPlayProgram3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyHttpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    6,   35,    2, 0x06 /* Public */,
      10,    1,   48,    2, 0x06 /* Public */,
      12,    7,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,    4,    5,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::QString,    4,    5,    6,    7,    8,    9,   11,

       0        // eod
};

void MyHttpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyHttpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalStart(); break;
        case 1: _t->signalPlayProgram1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 2: _t->signalPlayProgram2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->signalPlayProgram3((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyHttpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServer::signalStart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyHttpServer::*)(int , QString , int , QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServer::signalPlayProgram1)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyHttpServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServer::signalPlayProgram2)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyHttpServer::*)(int , QString , int , QString , int , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServer::signalPlayProgram3)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyHttpServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MyHttpServer.data,
    qt_meta_data_MyHttpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyHttpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyHttpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyHttpServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyHttpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MyHttpServer::signalStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyHttpServer::signalPlayProgram1(int _t1, QString _t2, int _t3, QString _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyHttpServer::signalPlayProgram2(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyHttpServer::signalPlayProgram3(int _t1, QString _t2, int _t3, QString _t4, int _t5, int _t6, QString _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
