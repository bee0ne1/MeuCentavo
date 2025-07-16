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
        "resumosRecebidos",
        "receitas",
        "despesas",
        "gastosPorCategoriaRecebidos",
        "QHash<QString,double>",
        "dadosGrafico",
        "erroOcorrido",
        "mensagem",
        "onAdicionarLancamentoReply",
        "QNetworkReply*",
        "reply",
        "onObterLancamentosReply",
        "onObterResumosReply",
        "onObterGastosCategoriaReply"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'lancamentoAdicionado'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lancamentosRecebidos'
        QtMocHelpers::SignalData<void(const QVector<Lancamento> &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Signal 'resumosRecebidos'
        QtMocHelpers::SignalData<void(double, double)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 7 }, { QMetaType::Double, 8 },
        }}),
        // Signal 'gastosPorCategoriaRecebidos'
        QtMocHelpers::SignalData<void(const QHash<QString,double> &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Signal 'erroOcorrido'
        QtMocHelpers::SignalData<void(const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Slot 'onAdicionarLancamentoReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'onObterLancamentosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'onObterResumosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'onObterGastosCategoriaReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
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
        case 2: _t->resumosRecebidos((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 3: _t->gastosPorCategoriaRecebidos((*reinterpret_cast< std::add_pointer_t<QHash<QString,double>>>(_a[1]))); break;
        case 4: _t->erroOcorrido((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onAdicionarLancamentoReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 6: _t->onObterLancamentosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 7: _t->onObterResumosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 8: _t->onObterGastosCategoriaReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::lancamentoAdicionado, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<Lancamento> & )>(_a, &LancamentoDAO::lancamentosRecebidos, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(double , double )>(_a, &LancamentoDAO::resumosRecebidos, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QHash<QString,double> & )>(_a, &LancamentoDAO::gastosPorCategoriaRecebidos, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QString & )>(_a, &LancamentoDAO::erroOcorrido, 4))
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
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
void LancamentoDAO::resumosRecebidos(double _t1, double _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void LancamentoDAO::gastosPorCategoriaRecebidos(const QHash<QString,double> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void LancamentoDAO::erroOcorrido(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
