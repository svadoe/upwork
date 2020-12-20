/****************************************************************************
** Meta object code from reading C++ file 'event_logger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../event_logger/event_logger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'event_logger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EventLogger_t {
    QByteArrayData data[11];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EventLogger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EventLogger_t qt_meta_stringdata_EventLogger = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EventLogger"
QT_MOC_LITERAL(1, 12, 18), // "local_socket_state"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 18), // "requestInputEvents"
QT_MOC_LITERAL(4, 51, 29), // "requestWorkspaceWatcherEvents"
QT_MOC_LITERAL(5, 81, 15), // "readInputEvents"
QT_MOC_LITERAL(6, 97, 20), // "readWorkspaceWatcher"
QT_MOC_LITERAL(7, 118, 12), // "displayError"
QT_MOC_LITERAL(8, 131, 30), // "QLocalSocket::LocalSocketError"
QT_MOC_LITERAL(9, 162, 11), // "socketError"
QT_MOC_LITERAL(10, 174, 29) // "save_input_events_to_database"

    },
    "EventLogger\0local_socket_state\0\0"
    "requestInputEvents\0requestWorkspaceWatcherEvents\0"
    "readInputEvents\0readWorkspaceWatcher\0"
    "displayError\0QLocalSocket::LocalSocketError\0"
    "socketError\0save_input_events_to_database"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EventLogger[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void EventLogger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EventLogger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->local_socket_state(); break;
        case 1: _t->requestInputEvents(); break;
        case 2: _t->requestWorkspaceWatcherEvents(); break;
        case 3: _t->readInputEvents(); break;
        case 4: _t->readWorkspaceWatcher(); break;
        case 5: _t->displayError((*reinterpret_cast< QLocalSocket::LocalSocketError(*)>(_a[1]))); break;
        case 6: _t->save_input_events_to_database(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EventLogger::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_EventLogger.data,
    qt_meta_data_EventLogger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EventLogger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EventLogger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EventLogger.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EventLogger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
