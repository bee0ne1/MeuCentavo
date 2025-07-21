/****************************************************************************
** Meta object code from reading C++ file 'formAdicionarLancamento.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Designer/FormsDashboard/formAdicionarLancamento.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formAdicionarLancamento.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN23formAdicionarLancamentoE_t {};
} // unnamed namespace

template <> constexpr inline auto formAdicionarLancamento::qt_create_metaobjectdata<qt_meta_tag_ZN23formAdicionarLancamentoE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "formAdicionarLancamento",
        "lancamentoSalvo",
        "",
        "salvarLancamento",
        "onContasRecebidas",
        "QList<Conta>",
        "contas",
        "onCategoriasRecebidas",
        "QList<Categoria>",
        "categorias",
        "onLancamentoAdicionado",
        "onErroDeRede",
        "motivo",
        "filtrarCategoriasPorTipo"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'lancamentoSalvo'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'salvarLancamento'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onContasRecebidas'
        QtMocHelpers::SlotData<void(const QVector<Conta> &)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'onCategoriasRecebidas'
        QtMocHelpers::SlotData<void(const QVector<Categoria> &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'onLancamentoAdicionado'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onErroDeRede'
        QtMocHelpers::SlotData<void(const QString &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Slot 'filtrarCategoriasPorTipo'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<formAdicionarLancamento, qt_meta_tag_ZN23formAdicionarLancamentoE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject formAdicionarLancamento::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23formAdicionarLancamentoE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23formAdicionarLancamentoE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN23formAdicionarLancamentoE_t>.metaTypes,
    nullptr
} };

void formAdicionarLancamento::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<formAdicionarLancamento *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->lancamentoSalvo(); break;
        case 1: _t->salvarLancamento(); break;
        case 2: _t->onContasRecebidas((*reinterpret_cast< std::add_pointer_t<QList<Conta>>>(_a[1]))); break;
        case 3: _t->onCategoriasRecebidas((*reinterpret_cast< std::add_pointer_t<QList<Categoria>>>(_a[1]))); break;
        case 4: _t->onLancamentoAdicionado(); break;
        case 5: _t->onErroDeRede((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->filtrarCategoriasPorTipo(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (formAdicionarLancamento::*)()>(_a, &formAdicionarLancamento::lancamentoSalvo, 0))
            return;
    }
}

const QMetaObject *formAdicionarLancamento::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *formAdicionarLancamento::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23formAdicionarLancamentoE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int formAdicionarLancamento::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void formAdicionarLancamento::lancamentoSalvo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
