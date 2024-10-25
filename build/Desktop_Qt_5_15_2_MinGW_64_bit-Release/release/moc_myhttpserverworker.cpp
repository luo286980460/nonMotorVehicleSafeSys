/****************************************************************************
** Meta object code from reading C++ file 'myhttpserverworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../myhttpserverworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myhttpserverworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyHttpServerWorker_t {
    QByteArrayData data[17];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyHttpServerWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyHttpServerWorker_t qt_meta_stringdata_MyHttpServerWorker = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MyHttpServerWorker"
QT_MOC_LITERAL(1, 19, 10), // "signalPost"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "url"
QT_MOC_LITERAL(4, 35, 4), // "data"
QT_MOC_LITERAL(5, 40, 18), // "signalPlayProgram1"
QT_MOC_LITERAL(6, 59, 8), // "fontSize"
QT_MOC_LITERAL(7, 68, 7), // "content"
QT_MOC_LITERAL(8, 76, 10), // "audioTimes"
QT_MOC_LITERAL(9, 87, 12), // "voiceContent"
QT_MOC_LITERAL(10, 100, 11), // "audioSwitch"
QT_MOC_LITERAL(11, 112, 11), // "audiovolume"
QT_MOC_LITERAL(12, 124, 18), // "signalPlayProgram2"
QT_MOC_LITERAL(13, 143, 6), // "base64"
QT_MOC_LITERAL(14, 150, 18), // "signalPlayProgram3"
QT_MOC_LITERAL(15, 169, 9), // "slotStart"
QT_MOC_LITERAL(16, 179, 4) // "post"

    },
    "MyHttpServerWorker\0signalPost\0\0url\0"
    "data\0signalPlayProgram1\0fontSize\0"
    "content\0audioTimes\0voiceContent\0"
    "audioSwitch\0audiovolume\0signalPlayProgram2\0"
    "base64\0signalPlayProgram3\0slotStart\0"
    "post"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyHttpServerWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    6,   49,    2, 0x06 /* Public */,
      12,    1,   62,    2, 0x06 /* Public */,
      14,    7,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   80,    2, 0x0a /* Public */,
      16,    2,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,    6,    7,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::QString,    6,    7,    8,    9,   10,   11,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,

       0        // eod
};

void MyHttpServerWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyHttpServerWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalPost((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->signalPlayProgram1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 2: _t->signalPlayProgram2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->signalPlayProgram3((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 4: _t->slotStart(); break;
        case 5: _t->post((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyHttpServerWorker::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServerWorker::signalPost)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyHttpServerWorker::*)(int , QString , int , QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServerWorker::signalPlayProgram1)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyHttpServerWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServerWorker::signalPlayProgram2)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyHttpServerWorker::*)(int , QString , int , QString , int , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyHttpServerWorker::signalPlayProgram3)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyHttpServerWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MyHttpServerWorker.data,
    qt_meta_data_MyHttpServerWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyHttpServerWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyHttpServerWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyHttpServerWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyHttpServerWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MyHttpServerWorker::signalPost(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyHttpServerWorker::signalPlayProgram1(int _t1, QString _t2, int _t3, QString _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyHttpServerWorker::signalPlayProgram2(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyHttpServerWorker::signalPlayProgram3(int _t1, QString _t2, int _t3, QString _t4, int _t5, int _t6, QString _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
