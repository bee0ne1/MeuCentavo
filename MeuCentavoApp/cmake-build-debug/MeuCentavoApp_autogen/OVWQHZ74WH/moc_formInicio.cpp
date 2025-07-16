/****************************************************************************
** Meta object code from reading C++ file 'formInicio.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Designer/formInicio.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formInicio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
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
struct qt_meta_tag_ZN10formInicioE_t {};
} // unnamed namespace

template <> constexpr inline auto formInicio::qt_create_metaobjectdata<qt_meta_tag_ZN10formInicioE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "formInicio",
        "abrirTelaSelecaoUsuario",
        "",
        "tentarLogin",
        "onUsuarioInicialRecebido",
        "std::optional<Usuario>",
        "usuario",
        "onUsuarioSelecionado",
        "Usuario",
        "onLoginSucesso",
        "token",
        "onLoginFalhou",
        "motivo"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'abrirTelaSelecaoUsuario'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'tentarLogin'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUsuarioInicialRecebido'
        QtMocHelpers::SlotData<void(const std::optional<Usuario> &)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'onUsuarioSelecionado'
        QtMocHelpers::SlotData<void(const Usuario &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 6 },
        }}),
        // Slot 'onLoginSucesso'
        QtMocHelpers::SlotData<void(const QString &, const Usuario &)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { 0x80000000 | 8, 6 },
        }}),
        // Slot 'onLoginFalhou'
        QtMocHelpers::SlotData<void(const QString &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<formInicio, qt_meta_tag_ZN10formInicioE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject formInicio::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10formInicioE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10formInicioE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10formInicioE_t>.metaTypes,
    nullptr
} };

void formInicio::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<formInicio *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->abrirTelaSelecaoUsuario(); break;
        case 1: _t->tentarLogin(); break;
        case 2: _t->onUsuarioInicialRecebido((*reinterpret_cast< std::add_pointer_t<std::optional<Usuario>>>(_a[1]))); break;
        case 3: _t->onUsuarioSelecionado((*reinterpret_cast< std::add_pointer_t<Usuario>>(_a[1]))); break;
        case 4: _t->onLoginSucesso((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Usuario>>(_a[2]))); break;
        case 5: _t->onLoginFalhou((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *formInicio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *formInicio::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10formInicioE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int formInicio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
