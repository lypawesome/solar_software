/****************************************************************************
** Meta object code from reading C++ file 'TopoTreeViewController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/TopoTreeViewController.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TopoTreeViewController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_solar__TopoTreeViewController_t {
    uint offsetsAndSizes[26];
    char stringdata0[30];
    char stringdata1[13];
    char stringdata2[20];
    char stringdata3[1];
    char stringdata4[15];
    char stringdata5[12];
    char stringdata6[6];
    char stringdata7[9];
    char stringdata8[11];
    char stringdata9[13];
    char stringdata10[12];
    char stringdata11[5];
    char stringdata12[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_solar__TopoTreeViewController_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_solar__TopoTreeViewController_t qt_meta_stringdata_solar__TopoTreeViewController = {
    {
        QT_MOC_LITERAL(0, 29),  // "solar::TopoTreeViewController"
        QT_MOC_LITERAL(30, 12),  // "getTreeModel"
        QT_MOC_LITERAL(43, 19),  // "QAbstractItemModel*"
        QT_MOC_LITERAL(63, 0),  // ""
        QT_MOC_LITERAL(64, 14),  // "updateNodeName"
        QT_MOC_LITERAL(79, 11),  // "QModelIndex"
        QT_MOC_LITERAL(91, 5),  // "index"
        QT_MOC_LITERAL(97, 8),  // "new_name"
        QT_MOC_LITERAL(106, 10),  // "updateNode"
        QT_MOC_LITERAL(117, 12),  // "getImageName"
        QT_MOC_LITERAL(130, 11),  // "appendChild"
        QT_MOC_LITERAL(142, 4),  // "type"
        QT_MOC_LITERAL(147, 15)   // "getTotalNodeCnt"
    },
    "solar::TopoTreeViewController",
    "getTreeModel",
    "QAbstractItemModel*",
    "",
    "updateNodeName",
    "QModelIndex",
    "index",
    "new_name",
    "updateNode",
    "getImageName",
    "appendChild",
    "type",
    "getTotalNodeCnt"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_solar__TopoTreeViewController[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    3, 0x0a,    1 /* Public */,
       4,    2,   51,    3, 0x0a,    2 /* Public */,
       8,    1,   56,    3, 0x0a,    5 /* Public */,
       9,    1,   59,    3, 0x0a,    7 /* Public */,
      10,    2,   62,    3, 0x0a,    9 /* Public */,
      12,    0,   67,    3, 0x0a,   12 /* Public */,

 // slots: parameters
    0x80000000 | 2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QVariant,    6,    7,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::QString, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,   11,
    QMetaType::Int,

       0        // eod
};

Q_CONSTINIT const QMetaObject solar::TopoTreeViewController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_solar__TopoTreeViewController.offsetsAndSizes,
    qt_meta_data_solar__TopoTreeViewController,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_solar__TopoTreeViewController_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TopoTreeViewController, std::true_type>,
        // method 'getTreeModel'
        QtPrivate::TypeAndForceComplete<QAbstractItemModel *, std::false_type>,
        // method 'updateNodeName'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        // method 'updateNode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'getImageName'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'appendChild'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'getTotalNodeCnt'
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void solar::TopoTreeViewController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TopoTreeViewController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { QAbstractItemModel* _r = _t->getTreeModel();
            if (_a[0]) *reinterpret_cast< QAbstractItemModel**>(_a[0]) = std::move(_r); }  break;
        case 1: _t->updateNodeName((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2]))); break;
        case 2: _t->updateNode((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 3: { QString _r = _t->getImageName((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->appendChild((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: { int _r = _t->getTotalNodeCnt();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *solar::TopoTreeViewController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *solar::TopoTreeViewController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_solar__TopoTreeViewController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int solar::TopoTreeViewController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
