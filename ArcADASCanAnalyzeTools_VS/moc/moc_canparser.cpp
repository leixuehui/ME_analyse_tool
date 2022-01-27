/****************************************************************************
** Meta object code from reading C++ file 'canparser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../canparser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canparser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CanParser_t {
    QByteArrayData data[10];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CanParser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CanParser_t qt_meta_stringdata_CanParser = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CanParser"
QT_MOC_LITERAL(1, 10, 20), // "signalDisplayObjData"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "DrawObjData"
QT_MOC_LITERAL(4, 44, 11), // "drawObjData"
QT_MOC_LITERAL(5, 56, 17), // "signalClearAllObj"
QT_MOC_LITERAL(6, 74, 26), // "signalUpdateDisplayMessage"
QT_MOC_LITERAL(7, 101, 27), // "QList<DisplayAndWarningMsg>"
QT_MOC_LITERAL(8, 129, 11), // "displayMsgs"
QT_MOC_LITERAL(9, 141, 29) // "signalFrameTxtAnalyzeFinished"

    },
    "CanParser\0signalDisplayObjData\0\0"
    "DrawObjData\0drawObjData\0signalClearAllObj\0"
    "signalUpdateDisplayMessage\0"
    "QList<DisplayAndWarningMsg>\0displayMsgs\0"
    "signalFrameTxtAnalyzeFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanParser[] = {

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
       1,    1,   34,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,
       6,    1,   38,    2, 0x06 /* Public */,
       9,    0,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void CanParser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CanParser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDisplayObjData((*reinterpret_cast< const DrawObjData(*)>(_a[1]))); break;
        case 1: _t->signalClearAllObj(); break;
        case 2: _t->signalUpdateDisplayMessage((*reinterpret_cast< const QList<DisplayAndWarningMsg>(*)>(_a[1]))); break;
        case 3: _t->signalFrameTxtAnalyzeFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CanParser::*)(const DrawObjData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanParser::signalDisplayObjData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CanParser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanParser::signalClearAllObj)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CanParser::*)(const QList<DisplayAndWarningMsg> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanParser::signalUpdateDisplayMessage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CanParser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanParser::signalFrameTxtAnalyzeFinished)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CanParser::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CanParser.data,
    qt_meta_data_CanParser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CanParser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanParser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CanParser.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CanParser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CanParser::signalDisplayObjData(const DrawObjData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CanParser::signalClearAllObj()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CanParser::signalUpdateDisplayMessage(const QList<DisplayAndWarningMsg> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CanParser::signalFrameTxtAnalyzeFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
