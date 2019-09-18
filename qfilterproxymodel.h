#ifndef QFILTERPROXYMODEL_H
#define QFILTERPROXYMODEL_H


#include <QSortFilterProxyModel>
class Veicolo;
/*
 * Classe proxy che funzionerà da intermediario fra QListModelAdapter e ListView
 * per permettere alla vista di visualizzare solo certi elementi (Veicolo) sulla base
 * dell'input di ricerca inserito pur non dovendo effettuare alcuna operazione
 * sul reale modello dei dati sottostante e senza duplicare dati.
 */
class QFilterProxyModel : public QSortFilterProxyModel {
public:
    QFilterProxyModel(QObject* = nullptr);
    bool insert(Veicolo* ,int, int = 1, const QModelIndex& = QModelIndex());
    bool modify(Veicolo* ,int);
    const Veicolo* getCar(const QModelIndex& index) const;

protected:
    bool filterAcceptsRow(int, const QModelIndex&) const override;
};

#endif // QFILTERPROXYMODEL_H
