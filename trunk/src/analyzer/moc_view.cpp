/****************************************************************************
** Meta object code from reading C++ file 'view.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "view.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_eMU__analyzer__View_t {
    QByteArrayData data[14];
    char stringdata[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_eMU__analyzer__View_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_eMU__analyzer__View_t qt_meta_stringdata_eMU__analyzer__View = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 14),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 5),
QT_MOC_LITERAL(4, 42, 14),
QT_MOC_LITERAL(5, 57, 28),
QT_MOC_LITERAL(6, 86, 14),
QT_MOC_LITERAL(7, 101, 27),
QT_MOC_LITERAL(8, 129, 26),
QT_MOC_LITERAL(9, 156, 10),
QT_MOC_LITERAL(10, 167, 11),
QT_MOC_LITERAL(11, 179, 21),
QT_MOC_LITERAL(12, 201, 23),
QT_MOC_LITERAL(13, 225, 20)
    },
    "eMU::analyzer::View\0loadReadStream\0\0"
    "index\0disconnectUser\0resizeWriteStreamFieldsCount\0"
    "numberOfFields\0parseReadStreamNumericField\0"
    "parseReadStreamStringField\0sendFields\0"
    "sendHexDump\0getWriteStreamHexDump\0"
    "clearWriteStreamHexDump\0clearWriteStreamView\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_eMU__analyzer__View[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a,
       4,    0,   67,    2, 0x0a,
       5,    1,   68,    2, 0x0a,
       7,    0,   71,    2, 0x0a,
       8,    0,   72,    2, 0x0a,
       9,    0,   73,    2, 0x0a,
      10,    0,   74,    2, 0x0a,
      11,    0,   75,    2, 0x0a,
      12,    0,   76,    2, 0x0a,
      13,    0,   77,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void eMU::analyzer::View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        View *_t = static_cast<View *>(_o);
        switch (_id) {
        case 0: _t->loadReadStream((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->disconnectUser(); break;
        case 2: _t->resizeWriteStreamFieldsCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->parseReadStreamNumericField(); break;
        case 4: _t->parseReadStreamStringField(); break;
        case 5: _t->sendFields(); break;
        case 6: _t->sendHexDump(); break;
        case 7: _t->getWriteStreamHexDump(); break;
        case 8: _t->clearWriteStreamHexDump(); break;
        case 9: _t->clearWriteStreamView(); break;
        default: ;
        }
    }
}

const QMetaObject eMU::analyzer::View::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_eMU__analyzer__View.data,
      qt_meta_data_eMU__analyzer__View,  qt_static_metacall, 0, 0}
};


const QMetaObject *eMU::analyzer::View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *eMU::analyzer::View::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_eMU__analyzer__View.stringdata))
        return static_cast<void*>(const_cast< View*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int eMU::analyzer::View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
