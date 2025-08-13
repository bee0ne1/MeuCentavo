/****************************************************************************
** Meta object code from reading C++ file 'formMainDashboard.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Designer/FormsDashboard/formMainDashboard.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formMainDashboard.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17formMainDashboardE_t {};
} // unnamed namespace

template <> constexpr inline auto formMainDashboard::qt_create_metaobjectdata<qt_meta_tag_ZN17formMainDashboardE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "formMainDashboard",
        "on_buttonHome_clicked",
        "",
        "on_buttonRelatorios_clicked",
        "on_buttonLancamentos_clicked",
        "on_buttonConfiguracoes_clicked",
        "on_buttonSwitchUsuario_clicked",
        "on_buttonMetas_clicked",
        "on_buttonInvestimentos_clicked",
        "on_buttonDividas_clicked",
        "onPerfisRecebidos",
        "QList<Perfil>",
        "perfis",
        "onPerfilAlterado",
        "index",
        "onNovoTokenRecebido",
        "novoToken",
        "Usuario",
        "usuario",
        "onListaDePerfisModificada"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_buttonHome_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_buttonRelatorios_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_buttonLancamentos_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_buttonConfiguracoes_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_buttonSwitchUsuario_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_buttonMetas_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_buttonInvestimentos_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_buttonDividas_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPerfisRecebidos'
        QtMocHelpers::SlotData<void(const QVector<Perfil> &)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'onPerfilAlterado'
        QtMocHelpers::SlotData<void(int)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
        // Slot 'onNovoTokenRecebido'
        QtMocHelpers::SlotData<void(const QString &, const Usuario &)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 16 }, { 0x80000000 | 17, 18 },
        }}),
        // Slot 'onListaDePerfisModificada'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<formMainDashboard, qt_meta_tag_ZN17formMainDashboardE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject formMainDashboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17formMainDashboardE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17formMainDashboardE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17formMainDashboardE_t>.metaTypes,
    nullptr
} };

void formMainDashboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<formMainDashboard *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_buttonHome_clicked(); break;
        case 1: _t->on_buttonRelatorios_clicked(); break;
        case 2: _t->on_buttonLancamentos_clicked(); break;
        case 3: _t->on_buttonConfiguracoes_clicked(); break;
        case 4: _t->on_buttonSwitchUsuario_clicked(); break;
        case 5: _t->on_buttonMetas_clicked(); break;
        case 6: _t->on_buttonInvestimentos_clicked(); break;
        case 7: _t->on_buttonDividas_clicked(); break;
        case 8: _t->onPerfisRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Perfil>>>(_a[1]))); break;
        case 9: _t->onPerfilAlterado((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->onNovoTokenRecebido((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Usuario>>(_a[2]))); break;
        case 11: _t->onListaDePerfisModificada(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<Perfil> >(); break;
            }
            break;
        }
    }
}

const QMetaObject *formMainDashboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *formMainDashboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17formMainDashboardE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int formMainDashboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
