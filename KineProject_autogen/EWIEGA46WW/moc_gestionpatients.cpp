/****************************************************************************
** Meta object code from reading C++ file 'gestionpatients.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gestionpatients.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestionpatients.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGestionPatientsENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSGestionPatientsENDCLASS = QtMocHelpers::stringData(
    "GestionPatients",
    "on_initialiserFenetreMere",
    "",
    "on_pushButton_ajouter_clicked",
    "on_pushButton_supprimer_clicked",
    "on_pushButton_modifier_clicked",
    "closeEvent",
    "QCloseEvent*",
    "event",
    "genererTablePatient"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGestionPatientsENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[16];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[30];
    char stringdata4[32];
    char stringdata5[31];
    char stringdata6[11];
    char stringdata7[13];
    char stringdata8[6];
    char stringdata9[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGestionPatientsENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGestionPatientsENDCLASS_t qt_meta_stringdata_CLASSGestionPatientsENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "GestionPatients"
        QT_MOC_LITERAL(16, 25),  // "on_initialiserFenetreMere"
        QT_MOC_LITERAL(42, 0),  // ""
        QT_MOC_LITERAL(43, 29),  // "on_pushButton_ajouter_clicked"
        QT_MOC_LITERAL(73, 31),  // "on_pushButton_supprimer_clicked"
        QT_MOC_LITERAL(105, 30),  // "on_pushButton_modifier_clicked"
        QT_MOC_LITERAL(136, 10),  // "closeEvent"
        QT_MOC_LITERAL(147, 12),  // "QCloseEvent*"
        QT_MOC_LITERAL(160, 5),  // "event"
        QT_MOC_LITERAL(166, 19)   // "genererTablePatient"
    },
    "GestionPatients",
    "on_initialiserFenetreMere",
    "",
    "on_pushButton_ajouter_clicked",
    "on_pushButton_supprimer_clicked",
    "on_pushButton_modifier_clicked",
    "closeEvent",
    "QCloseEvent*",
    "event",
    "genererTablePatient"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGestionPatientsENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    1,   54,    2, 0x08,    5 /* Private */,
       9,    0,   57,    2, 0x08,    7 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GestionPatients::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSGestionPatientsENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGestionPatientsENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGestionPatientsENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GestionPatients, std::true_type>,
        // method 'on_initialiserFenetreMere'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_ajouter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_supprimer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_modifier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCloseEvent *, std::false_type>,
        // method 'genererTablePatient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GestionPatients::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GestionPatients *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_initialiserFenetreMere(); break;
        case 1: _t->on_pushButton_ajouter_clicked(); break;
        case 2: _t->on_pushButton_supprimer_clicked(); break;
        case 3: _t->on_pushButton_modifier_clicked(); break;
        case 4: _t->closeEvent((*reinterpret_cast< std::add_pointer_t<QCloseEvent*>>(_a[1]))); break;
        case 5: _t->genererTablePatient(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GestionPatients::*)();
            if (_t _q_method = &GestionPatients::on_initialiserFenetreMere; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *GestionPatients::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestionPatients::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGestionPatientsENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GestionPatients::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GestionPatients::on_initialiserFenetreMere()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
