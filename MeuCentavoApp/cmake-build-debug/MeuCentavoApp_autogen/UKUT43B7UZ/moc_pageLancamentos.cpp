/****************************************************************************
** Meta object code from reading C++ file 'pageLancamentos.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Designer/FormsDashboard/DashboardPages/pageLancamentos.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pageLancamentos.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15pageLancamentosE_t {};
} // unnamed namespace

template <> constexpr inline auto pageLancamentos::qt_create_metaobjectdata<qt_meta_tag_ZN15pageLancamentosE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "pageLancamentos",
        "dadosAtualizados",
        "",
        "carregarTabela",
        "onOcrConcluido",
        "QList<TransacaoImportada>",
        "transacoes",
        "abrirDialogoAdicionar",
        "onLancamentosRecebidos",
        "QList<Lancamento>",
        "lancamentos",
        "onErroDeRede",
        "motivo",
        "editarLancamento",
        "Lancamento",
        "lancamento",
        "excluirLancamento",
        "onContasRecebidas",
        "QList<Conta>",
        "contas",
        "on_buttonImportarExtrato_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'dadosAtualizados'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'carregarTabela'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onOcrConcluido'
        QtMocHelpers::SlotData<void(const QVector<TransacaoImportada> &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'abrirDialogoAdicionar'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onLancamentosRecebidos'
        QtMocHelpers::SlotData<void(const QVector<Lancamento> &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Slot 'onErroDeRede'
        QtMocHelpers::SlotData<void(const QString &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Slot 'editarLancamento'
        QtMocHelpers::SlotData<void(const Lancamento &)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Slot 'excluirLancamento'
        QtMocHelpers::SlotData<void(const Lancamento &)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Slot 'onContasRecebidas'
        QtMocHelpers::SlotData<void(const QVector<Conta> &)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 18, 19 },
        }}),
        // Slot 'on_buttonImportarExtrato_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<pageLancamentos, qt_meta_tag_ZN15pageLancamentosE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject pageLancamentos::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15pageLancamentosE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15pageLancamentosE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15pageLancamentosE_t>.metaTypes,
    nullptr
} };

void pageLancamentos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<pageLancamentos *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->dadosAtualizados(); break;
        case 1: _t->carregarTabela(); break;
        case 2: _t->onOcrConcluido((*reinterpret_cast< std::add_pointer_t<QList<TransacaoImportada>>>(_a[1]))); break;
        case 3: _t->abrirDialogoAdicionar(); break;
        case 4: _t->onLancamentosRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Lancamento>>>(_a[1]))); break;
        case 5: _t->onErroDeRede((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->editarLancamento((*reinterpret_cast< std::add_pointer_t<Lancamento>>(_a[1]))); break;
        case 7: _t->excluirLancamento((*reinterpret_cast< std::add_pointer_t<Lancamento>>(_a[1]))); break;
        case 8: _t->onContasRecebidas((*reinterpret_cast< std::add_pointer_t<QList<Conta>>>(_a[1]))); break;
        case 9: _t->on_buttonImportarExtrato_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (pageLancamentos::*)()>(_a, &pageLancamentos::dadosAtualizados, 0))
            return;
    }
}

const QMetaObject *pageLancamentos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pageLancamentos::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15pageLancamentosE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int pageLancamentos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void pageLancamentos::dadosAtualizados()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
