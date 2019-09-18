#include "qfilterproxymodel.h"
#include "qlistmodeladapter.h"

QFilterProxyModel::QFilterProxyModel(QObject* parent) : QSortFilterProxyModel (parent) {

}

bool QFilterProxyModel::insert(Veicolo* v, int begin, int count, const QModelIndex& parent) {
    bool result = static_cast<QListModelAdapter*>(sourceModel())->insert(v,begin, count, parent);
    invalidateFilter();
    return result;
}

bool QFilterProxyModel::modify(Veicolo* v,int index){
    bool result = static_cast<QListModelAdapter*>(sourceModel())->modify(v,index);
    invalidateFilter();
    return result;
}

bool QFilterProxyModel::filterAcceptsRow(int row_source, const QModelIndex&) const {
    // ritornare true se la targa del veicolo matcha una RegExp
    // altrimenti ritorna false
    QModelIndex index_source = sourceModel()->index(row_source, 0);

    return sourceModel()->data(index_source).toString().contains(filterRegExp());

}

const Veicolo* QFilterProxyModel::getCar(const QModelIndex& index) const {
    QModelIndex index_source = mapToSource(index);
    return static_cast<QListModelAdapter*>(sourceModel())->getcar(index_source);
}

