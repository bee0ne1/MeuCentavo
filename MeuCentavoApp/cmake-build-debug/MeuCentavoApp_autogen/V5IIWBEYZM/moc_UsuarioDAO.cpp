/****************************************************************************
** Meta object code from reading C++ file 'UsuarioDAO.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../DataAccess/UsuarioDAO.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UsuarioDAO.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10UsuarioDAOE_t {};
} // unnamed namespace

template <> constexpr inline auto UsuarioDAO::qt_create_metaobjectdata<qt_meta_tag_ZN10UsuarioDAOE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UsuarioDAO",
        "registroSucesso",
        "",
        "loginSucesso",
        "token",
        "Usuario",
        "usuario",
        "todosUsuariosRecebidos",
        "QList<Usuario>",
        "usuarios",
        "erroDeAutenticacao",
        "mensagem",
        "erroDeRede",
        "usuarioInicialRecebido",
        "std::optional<Usuario>",
        "registroFalhou",
        "motivo",
        "remocaoSucesso",
        "onRegistroReply",
        "QNetworkReply*",
        "reply",
        "onLoginReply",
        "onObterTodosReply",
        "onUsuarioInicialReply",
        "onRemoverUsuarioReply"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'registroSucesso'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'loginSucesso'
        QtMocHelpers::SignalData<void(const QString &, const Usuario &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'todosUsuariosRecebidos'
        QtMocHelpers::SignalData<void(const QVector<Usuario> &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Signal 'erroDeAutenticacao'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'erroDeRede'
        QtMocHelpers::SignalData<void(const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'usuarioInicialRecebido'
        QtMocHelpers::SignalData<void(const std::optional<Usuario> &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 6 },
        }}),
        // Signal 'registroFalhou'
        QtMocHelpers::SignalData<void(const QString &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Signal 'remocaoSucesso'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onRegistroReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'onLoginReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'onObterTodosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'onUsuarioInicialReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'onRemoverUsuarioReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UsuarioDAO, qt_meta_tag_ZN10UsuarioDAOE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UsuarioDAO::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10UsuarioDAOE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10UsuarioDAOE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10UsuarioDAOE_t>.metaTypes,
    nullptr
} };

void UsuarioDAO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UsuarioDAO *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->registroSucesso(); break;
        case 1: _t->loginSucesso((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Usuario>>(_a[2]))); break;
        case 2: _t->todosUsuariosRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Usuario>>>(_a[1]))); break;
        case 3: _t->erroDeAutenticacao((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->erroDeRede((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->usuarioInicialRecebido((*reinterpret_cast< std::add_pointer_t<std::optional<Usuario>>>(_a[1]))); break;
        case 6: _t->registroFalhou((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->remocaoSucesso(); break;
        case 8: _t->onRegistroReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 9: _t->onLoginReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 10: _t->onObterTodosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 11: _t->onUsuarioInicialReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 12: _t->onRemoverUsuarioReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)()>(_a, &UsuarioDAO::registroSucesso, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)(const QString & , const Usuario & )>(_a, &UsuarioDAO::loginSucesso, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)(const QVector<Usuario> & )>(_a, &UsuarioDAO::todosUsuariosRecebidos, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)(const QString & )>(_a, &UsuarioDAO::erroDeAutenticacao, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)(const QString & )>(_a, &UsuarioDAO::erroDeRede, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)(const std::optional<Usuario> & )>(_a, &UsuarioDAO::usuarioInicialRecebido, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)(const QString & )>(_a, &UsuarioDAO::registroFalhou, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (UsuarioDAO::*)()>(_a, &UsuarioDAO::remocaoSucesso, 7))
            return;
    }
}

const QMetaObject *UsuarioDAO::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UsuarioDAO::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10UsuarioDAOE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UsuarioDAO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void UsuarioDAO::registroSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UsuarioDAO::loginSucesso(const QString & _t1, const Usuario & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void UsuarioDAO::todosUsuariosRecebidos(const QVector<Usuario> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void UsuarioDAO::erroDeAutenticacao(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void UsuarioDAO::erroDeRede(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void UsuarioDAO::usuarioInicialRecebido(const std::optional<Usuario> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void UsuarioDAO::registroFalhou(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void UsuarioDAO::remocaoSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
