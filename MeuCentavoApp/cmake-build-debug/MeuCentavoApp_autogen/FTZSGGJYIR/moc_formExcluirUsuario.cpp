/****************************************************************************
** Meta object code from reading C++ file 'formExcluirUsuario.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Designer/FormsLogin/formExcluirUsuario.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formExcluirUsuario.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18formExcluirUsuarioE_t {};
} // unnamed namespace

template <> constexpr inline auto formExcluirUsuario::qt_create_metaobjectdata<qt_meta_tag_ZN18formExcluirUsuarioE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "formExcluirUsuario",
        "exclusaoFechada",
        "",
        "listaDeUsuariosModificada",
        "confirmarExclusaoUsuario",
        "Usuario",
        "usuario",
        "onUsuariosRecebidos",
        "QList<Usuario>",
        "usuarios",
        "onRemocaoSucesso",
        "onErro",
        "motivo"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'exclusaoFechada'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'listaDeUsuariosModificada'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'confirmarExclusaoUsuario'
        QtMocHelpers::SlotData<void(const Usuario &)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'onUsuariosRecebidos'
        QtMocHelpers::SlotData<void(const QVector<Usuario> &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'onRemocaoSucesso'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onErro'
        QtMocHelpers::SlotData<void(const QString &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<formExcluirUsuario, qt_meta_tag_ZN18formExcluirUsuarioE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject formExcluirUsuario::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18formExcluirUsuarioE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18formExcluirUsuarioE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18formExcluirUsuarioE_t>.metaTypes,
    nullptr
} };

void formExcluirUsuario::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<formExcluirUsuario *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->exclusaoFechada(); break;
        case 1: _t->listaDeUsuariosModificada(); break;
        case 2: _t->confirmarExclusaoUsuario((*reinterpret_cast< std::add_pointer_t<Usuario>>(_a[1]))); break;
        case 3: _t->onUsuariosRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Usuario>>>(_a[1]))); break;
        case 4: _t->onRemocaoSucesso(); break;
        case 5: _t->onErro((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (formExcluirUsuario::*)()>(_a, &formExcluirUsuario::exclusaoFechada, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (formExcluirUsuario::*)()>(_a, &formExcluirUsuario::listaDeUsuariosModificada, 1))
            return;
    }
}

const QMetaObject *formExcluirUsuario::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *formExcluirUsuario::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18formExcluirUsuarioE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int formExcluirUsuario::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void formExcluirUsuario::exclusaoFechada()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void formExcluirUsuario::listaDeUsuariosModificada()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
