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
        "lancamentoModificadoComSucesso",
        "lancamentoExcluidoComSucesso",
        "contasRecebidas",
        "QList<Conta>",
        "contas",
        "categoriasRecebidas",
        "QList<Categoria>",
        "categorias",
        "categoriaModificadaComSucesso",
        "contaModificadaComSucesso",
        "comparativoMensalRecebido",
        "QList<ResumoMensal>",
        "resumo",
        "metasRecebidas",
        "QList<Meta>",
        "metas",
        "metaModificadaComSucesso",
        "ativosRecebidos",
        "QList<Ativo>",
        "ativos",
        "ativoModificadoComSucesso",
        "operacoesRecebidas",
        "QList<OperacaoInvestimento>",
        "operacoes",
        "operacaoModificadaComSucesso",
        "performancePortfolioRecebida",
        "custoTotal",
        "valorMercado",
        "rentabilidadeValor",
        "rentabilidadePercentual",
        "dividendoAdicionadoComSucesso",
        "dividendosRecebidos",
        "QList<Dividendo>",
        "dividendos",
        "historicoPatrimonioRecebido",
        "QList<HistoricoPatrimonio>",
        "historico",
        "tendenciaCategoriaRecebida",
        "QList<PontoTendencia>",
        "tendencia",
        "planoSimuladoRecebido",
        "QList<LinhaCronograma>",
        "cronograma",
        "mesesTotais",
        "onAdicionarLancamentoReply",
        "QNetworkReply*",
        "reply",
        "onObterLancamentosReply",
        "onObterResumosReply",
        "onObterGastosCategoriaReply",
        "onObterContasReply",
        "onObterCategoriasReply",
        "onModificarCategoriaReply",
        "onObterComparativoMensalReply",
        "onMetasReply",
        "onModificarMetaReply",
        "onAtivosReply",
        "onModificarAtivoReply",
        "onOperacoesReply",
        "onModificarOperacaoReply",
        "onDividendosReply",
        "onPlanoSimuladoReply"
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
        // Signal 'lancamentoModificadoComSucesso'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lancamentoExcluidoComSucesso'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'contasRecebidas'
        QtMocHelpers::SignalData<void(const QVector<Conta> &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Signal 'categoriasRecebidas'
        QtMocHelpers::SignalData<void(const QVector<Categoria> &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 21 },
        }}),
        // Signal 'categoriaModificadaComSucesso'
        QtMocHelpers::SignalData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'contaModificadaComSucesso'
        QtMocHelpers::SignalData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'comparativoMensalRecebido'
        QtMocHelpers::SignalData<void(const QVector<ResumoMensal> &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 25, 26 },
        }}),
        // Signal 'metasRecebidas'
        QtMocHelpers::SignalData<void(const QVector<Meta> &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 28, 29 },
        }}),
        // Signal 'metaModificadaComSucesso'
        QtMocHelpers::SignalData<void()>(30, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'ativosRecebidos'
        QtMocHelpers::SignalData<void(const QVector<Ativo> &)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 32, 33 },
        }}),
        // Signal 'ativoModificadoComSucesso'
        QtMocHelpers::SignalData<void()>(34, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'operacoesRecebidas'
        QtMocHelpers::SignalData<void(const QVector<OperacaoInvestimento> &)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 36, 37 },
        }}),
        // Signal 'operacaoModificadaComSucesso'
        QtMocHelpers::SignalData<void()>(38, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'performancePortfolioRecebida'
        QtMocHelpers::SignalData<void(double, double, double, double)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 40 }, { QMetaType::Double, 41 }, { QMetaType::Double, 42 }, { QMetaType::Double, 43 },
        }}),
        // Signal 'dividendoAdicionadoComSucesso'
        QtMocHelpers::SignalData<void()>(44, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'dividendosRecebidos'
        QtMocHelpers::SignalData<void(const QVector<Dividendo> &)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 46, 47 },
        }}),
        // Signal 'historicoPatrimonioRecebido'
        QtMocHelpers::SignalData<void(const QVector<HistoricoPatrimonio> &)>(48, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 49, 50 },
        }}),
        // Signal 'tendenciaCategoriaRecebida'
        QtMocHelpers::SignalData<void(const QVector<PontoTendencia> &)>(51, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 52, 53 },
        }}),
        // Signal 'planoSimuladoRecebido'
        QtMocHelpers::SignalData<void(const QVector<LinhaCronograma> &, int)>(54, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 55, 56 }, { QMetaType::Int, 57 },
        }}),
        // Slot 'onAdicionarLancamentoReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(58, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onObterLancamentosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(61, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onObterResumosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(62, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onObterGastosCategoriaReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(63, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onObterContasReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(64, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onObterCategoriasReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(65, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onModificarCategoriaReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(66, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onObterComparativoMensalReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(67, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onMetasReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(68, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onModificarMetaReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(69, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onAtivosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(70, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onModificarAtivoReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(71, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onOperacoesReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(72, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onModificarOperacaoReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(73, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onDividendosReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(74, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
        }}),
        // Slot 'onPlanoSimuladoReply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(75, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 59, 60 },
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
        case 5: _t->lancamentoModificadoComSucesso(); break;
        case 6: _t->lancamentoExcluidoComSucesso(); break;
        case 7: _t->contasRecebidas((*reinterpret_cast< std::add_pointer_t<QList<Conta>>>(_a[1]))); break;
        case 8: _t->categoriasRecebidas((*reinterpret_cast< std::add_pointer_t<QList<Categoria>>>(_a[1]))); break;
        case 9: _t->categoriaModificadaComSucesso(); break;
        case 10: _t->contaModificadaComSucesso(); break;
        case 11: _t->comparativoMensalRecebido((*reinterpret_cast< std::add_pointer_t<QList<ResumoMensal>>>(_a[1]))); break;
        case 12: _t->metasRecebidas((*reinterpret_cast< std::add_pointer_t<QList<Meta>>>(_a[1]))); break;
        case 13: _t->metaModificadaComSucesso(); break;
        case 14: _t->ativosRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Ativo>>>(_a[1]))); break;
        case 15: _t->ativoModificadoComSucesso(); break;
        case 16: _t->operacoesRecebidas((*reinterpret_cast< std::add_pointer_t<QList<OperacaoInvestimento>>>(_a[1]))); break;
        case 17: _t->operacaoModificadaComSucesso(); break;
        case 18: _t->performancePortfolioRecebida((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 19: _t->dividendoAdicionadoComSucesso(); break;
        case 20: _t->dividendosRecebidos((*reinterpret_cast< std::add_pointer_t<QList<Dividendo>>>(_a[1]))); break;
        case 21: _t->historicoPatrimonioRecebido((*reinterpret_cast< std::add_pointer_t<QList<HistoricoPatrimonio>>>(_a[1]))); break;
        case 22: _t->tendenciaCategoriaRecebida((*reinterpret_cast< std::add_pointer_t<QList<PontoTendencia>>>(_a[1]))); break;
        case 23: _t->planoSimuladoRecebido((*reinterpret_cast< std::add_pointer_t<QList<LinhaCronograma>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 24: _t->onAdicionarLancamentoReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 25: _t->onObterLancamentosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 26: _t->onObterResumosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 27: _t->onObterGastosCategoriaReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 28: _t->onObterContasReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 29: _t->onObterCategoriasReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 30: _t->onModificarCategoriaReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 31: _t->onObterComparativoMensalReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 32: _t->onMetasReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 33: _t->onModificarMetaReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 34: _t->onAtivosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 35: _t->onModificarAtivoReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 36: _t->onOperacoesReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 37: _t->onModificarOperacaoReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 38: _t->onDividendosReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 39: _t->onPlanoSimuladoReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
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
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::lancamentoModificadoComSucesso, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::lancamentoExcluidoComSucesso, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<Conta> & )>(_a, &LancamentoDAO::contasRecebidas, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<Categoria> & )>(_a, &LancamentoDAO::categoriasRecebidas, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::categoriaModificadaComSucesso, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::contaModificadaComSucesso, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<ResumoMensal> & )>(_a, &LancamentoDAO::comparativoMensalRecebido, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<Meta> & )>(_a, &LancamentoDAO::metasRecebidas, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::metaModificadaComSucesso, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<Ativo> & )>(_a, &LancamentoDAO::ativosRecebidos, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::ativoModificadoComSucesso, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<OperacaoInvestimento> & )>(_a, &LancamentoDAO::operacoesRecebidas, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::operacaoModificadaComSucesso, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(double , double , double , double )>(_a, &LancamentoDAO::performancePortfolioRecebida, 18))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)()>(_a, &LancamentoDAO::dividendoAdicionadoComSucesso, 19))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<Dividendo> & )>(_a, &LancamentoDAO::dividendosRecebidos, 20))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<HistoricoPatrimonio> & )>(_a, &LancamentoDAO::historicoPatrimonioRecebido, 21))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<PontoTendencia> & )>(_a, &LancamentoDAO::tendenciaCategoriaRecebida, 22))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancamentoDAO::*)(const QVector<LinhaCronograma> & , int )>(_a, &LancamentoDAO::planoSimuladoRecebido, 23))
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
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 40;
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

// SIGNAL 5
void LancamentoDAO::lancamentoModificadoComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void LancamentoDAO::lancamentoExcluidoComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void LancamentoDAO::contasRecebidas(const QVector<Conta> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void LancamentoDAO::categoriasRecebidas(const QVector<Categoria> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void LancamentoDAO::categoriaModificadaComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void LancamentoDAO::contaModificadaComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void LancamentoDAO::comparativoMensalRecebido(const QVector<ResumoMensal> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
void LancamentoDAO::metasRecebidas(const QVector<Meta> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void LancamentoDAO::metaModificadaComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void LancamentoDAO::ativosRecebidos(const QVector<Ativo> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1);
}

// SIGNAL 15
void LancamentoDAO::ativoModificadoComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void LancamentoDAO::operacoesRecebidas(const QVector<OperacaoInvestimento> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 16, nullptr, _t1);
}

// SIGNAL 17
void LancamentoDAO::operacaoModificadaComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void LancamentoDAO::performancePortfolioRecebida(double _t1, double _t2, double _t3, double _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 18, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 19
void LancamentoDAO::dividendoAdicionadoComSucesso()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void LancamentoDAO::dividendosRecebidos(const QVector<Dividendo> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 20, nullptr, _t1);
}

// SIGNAL 21
void LancamentoDAO::historicoPatrimonioRecebido(const QVector<HistoricoPatrimonio> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 21, nullptr, _t1);
}

// SIGNAL 22
void LancamentoDAO::tendenciaCategoriaRecebida(const QVector<PontoTendencia> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 22, nullptr, _t1);
}

// SIGNAL 23
void LancamentoDAO::planoSimuladoRecebido(const QVector<LinhaCronograma> & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 23, nullptr, _t1, _t2);
}
QT_WARNING_POP
