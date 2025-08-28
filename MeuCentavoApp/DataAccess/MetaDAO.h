#ifndef METADAO_H
#define METADAO_H

#include <QObject>
#include <QVector>
#include "Modelo/Meta.h"

// Forward declarations
class QNetworkAccessManager;
class QNetworkReply;

class MetaDAO : public QObject
{
    Q_OBJECT
public:
    explicit MetaDAO(QObject *parent = nullptr);

    // Métodos de Metas
    void obterTodasMetas(const QString& token);
    void adicionarMeta(const Meta& meta, const QString& token);
    void editarMeta(const Meta& meta, const QString& token);
    void excluirMeta(int idMeta, const QString& token);

signals:
    void metasRecebidas(const QVector<Meta>& metas);
    void metaModificadaComSucesso();
    void onMetaError(const QString& mensagem);

private slots:
    void onMetasReply();
    void onModificarMetaReply();

private:
    QNetworkAccessManager *m_manager;
};

#endif // METADAO_H