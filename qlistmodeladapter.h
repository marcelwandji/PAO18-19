#ifndef QLISTMODELADAPTER_H
#define QLISTMODELADAPTER_H

#include <QAbstractListModel>
#include "modello.h"

//class Modello;

class QListModelAdapter : public QAbstractListModel {

private:
    Modello* modello;

public:
    QListModelAdapter(QObject* parent = nullptr);
    ~QListModelAdapter() override;

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const override;

    bool insert(Veicolo* ,int, int = 1, const QModelIndex& = QModelIndex());
    bool modify(Veicolo* ,int);
    bool removeRows(int, int = 1, const QModelIndex& = QModelIndex()) override;

    void saveToFile() const;
    void loadFromFile();
    Modello* getModello() const;
    const Veicolo* getcar( const QModelIndex& index)const;
    void cancella();
};

#endif // QLISTMODELADAPTER_H
