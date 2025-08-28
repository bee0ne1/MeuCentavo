/****************************************************************************
** Meta object code from reading C++ file 'LancamentoDAO.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../DataAccess/LancamentoDAO.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LancamentoDAO.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13LancamentoDAOE_t {};
} // unnamed namespace

template <> constexpr inline auto LancamentoDAO::qt_create_metaobjectdata<qt_meta_tag_ZN13LancamentoDAOE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "LancamentoDAO",
        "lancamentoAdicionado",
        "",
        "lancamentosRecebidos",
        "QList<Lancamento>",
        "lancamentos",
        "lancamentoModificadoComSucesso",
        "lancamentoExcluidoComSucesso",
        "ocrProcessadoComSucesso",
        "QList<TransacaoImportada>",
        "transacoes",
        "sugestoesRecebidas",
        "QMap<QString,int>",
        "mapaDeSugestoes",
        "connectTokenRecebido",
        "connectToken",
        "onLancamentoError",
        "mensagem",
        "onAdicionarLancamentoReply",
        "QNetworkReply*",
        "reply",
        "onObterLancamentosReply",
        "onSugestoesReply",
        "onConnectTokenReply"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'lancamentoAdicionado'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lancamentosRecebidos'
        QtMocHelpers::SignalData<void(const QVector<Lancamento> &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Signal 'lancamentoModificadoComSucesso'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lancamentoExcluidoComSucesso'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'ocrProcessadoComSucesso'
        QtMocHelpers::SignalData<void(const QVector<TransacaoImportada> &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'sugestoesRecebidas'
        QtMocHelpers::SignalData<void(const QMap<QString,int> &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Signal 'connectTokenRecebido'
        QtMocHelpers::SignalData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Signal 'onLancamentoError'
        QtMocHelpers::SignalData<void(const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Slot 'onAdicionarLancamentoReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'onObterLancamentosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'onSugestoesReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'onConnectTokenReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LancamentoDAO, qt_meta_tag_ZN13LancamentoDAOE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject LancamentoDAO::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13LancamentoDAOE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13LancamentoDAOE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13LancamentoDAOE_t>.metaTypes,
    nullptr
} };

void LancamentoDAO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LancamentoDAO *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->lancamentoAdicionado(); break;
        case 1: _t->lancamentosRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Lancamento>>>(_a[1]))); break;
        case 2: _t->lancamentoModificadoComSucesso(); break;
        case 3: _t->lancamentoExcluidoComSucesso(); break;
        case 4: _t->ocrProcessadoComSucesso((*reinterpret_cast< std::add_pointer_t<QList<TransacaoImportada>>>(_a[1]))); break;
        case 5: _t->sugestoesRecebidas((*reinterpret_cast< std::add_pointer_t<QMap<QString,int>>>(_a[1]))); break;
        case 6: _t->connectTokenRecebido((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onLancamentoError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->onAdicionarLancamentoReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 9: _t->onObterLancamentosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 10: _t->onSugestoesReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 11: _t->onConnectTokenReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::lancamentoAdicionado, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<Lancamento> & )>(_a, &LancamentoDAO::lancamentosRecebidos, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::lancamentoModificadoComSucesso, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::lancamentoExcluidoComSucesso, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<TransacaoImportada> & )>(_a, &LancamentoDAO::ocrProcessadoComSucesso, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QMap<QString,int> & )>(_a, &LancamentoDAO::sugestoesRecebidas, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QString & )>(_a, &LancamentoDAO::connectTokenRecebido, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QString & )>(_a, &LancamentoDAO::onLancamentoError, 7))
            return;
    }
}

const QMetaObject *LancamentoDAO::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LancamentoDAO::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13LancamentoDAOE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LancamentoDAO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void LancamentoDAO::lancamentoAdicionado()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LancamentoDAO::lancamentosRecebidos(const QVector<Lancamento> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void LancamentoDAO::lancamentoModificadoComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LancamentoDAO::lancamentoExcluidoComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LancamentoDAO::ocrProcessadoComSucesso(const QVector<TransacaoImportada> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void LancamentoDAO::sugestoesRecebidas(const QMap<QString,int> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void LancamentoDAO::connectTokenRecebido(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void LancamentoDAO::onLancamentoError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
