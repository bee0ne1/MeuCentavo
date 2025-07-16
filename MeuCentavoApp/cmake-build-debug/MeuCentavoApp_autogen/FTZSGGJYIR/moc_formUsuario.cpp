/****************************************************************************
** Meta object code from reading C++ file 'formUsuario.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Designer/FormsLogin/formUsuario.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formUsuario.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11formUsuarioE_t {};
} // unnamed namespace

template <> constexpr inline auto formUsuario::qt_create_metaobjectdata<qt_meta_tag_ZN11formUsuarioE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "formUsuario",
        "usuarioSelecionado",
        "",
        "Usuario",
        "usuario",
        "fechado",
        "abrirTelaCadastro",
        "abrirTelaExcluir",
        "onUsuariosRecebidos",
        "QList<Usuario>",
        "usuarios",
        "onErroDeRede",
        "motivo"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'usuarioSelecionado'
        QtMocHelpers::SignalData<void(const Usuario &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'fechado'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'abrirTelaCadastro'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'abrirTelaExcluir'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUsuariosRecebidos'
        QtMocHelpers::SlotData<void(const QVector<Usuario> &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Slot 'onErroDeRede'
        QtMocHelpers::SlotData<void(const QString &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<formUsuario, qt_meta_tag_ZN11formUsuarioE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject formUsuario::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11formUsuarioE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11formUsuarioE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11formUsuarioE_t>.metaTypes,
    nullptr
} };

void formUsuario::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<formUsuario *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->usuarioSelecionado((*reinterpret_cast< std::add_pointer_t<Usuario>>(_a[1]))); break;
        case 1: _t->fechado(); break;
        case 2: _t->abrirTelaCadastro(); break;
        case 3: _t->abrirTelaExcluir(); break;
        case 4: _t->onUsuariosRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Usuario>>>(_a[1]))); break;
        case 5: _t->onErroDeRede((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (formUsuario::*)(const Usuario & )>(_a, &formUsuario::usuarioSelecionado, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (formUsuario::*)()>(_a, &formUsuario::fechado, 1))
            return;
    }
}

const QMetaObject *formUsuario::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *formUsuario::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11formUsuarioE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int formUsuario::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void formUsuario::usuarioSelecionado(const Usuario & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void formUsuario::fechado()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
