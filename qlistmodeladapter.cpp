#include "qlistmodeladapter.h"

#include <QFont>
#include <QIcon>

QListModelAdapter::QListModelAdapter(QObject* parent) :
    QAbstractListModel(parent),
    modello(new Modello()){}

QListModelAdapter::~QListModelAdapter() {
    delete modello;
}

/*
 * Ritorna la dimensione (numero di righe) del modello
 */
int QListModelAdapter::rowCount(const QModelIndex&) const {
    return modello->contaVeicolo();
}

QVariant QListModelAdapter::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= modello->contaVeicolo())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return QString::fromStdString(modello->getVeicolo(index.row())->tipoVeicolo()+ '\n'+"M. "
                                      +modello->getVeicolo(index.row())->getModello()+ '\n'+"T. "
                                      +modello->getVeicolo(index.row())->getTarga()+ '\n'+"A. "
                                      +modello->getVeicolo(index.row())->getAlimentazione());
    }

    if(role == Qt::DecorationRole){
        const string type = modello->getVeicolo(index.row())->tipoVeicolo();
        const bool control = modello->getVeicolo(index.row())->controllaTarga();

        if(control == false){
            QIcon man(QIcon(":/images/attention.png"));
            return man;
        }

        if(type == "Autovettura"){
            QIcon man(QIcon(":/images/auto.png"));
            return man;
        }

        if(type == "Moto"){
            QIcon man(QIcon(":/images/moto.png"));
            return man;
        }

        if(type == "Camion"){
            QIcon man(QIcon(":/images/camion.png"));
            return man;
        }

    }

    if (role == Qt::FontRole) {
        const string type = modello->getVeicolo(index.row())->tipoVeicolo();
        if (type == "Autovettura") {
            QFont font("Arial", 10,QFont::Thin);
            font.setCapitalization(QFont::AllUppercase);
            return font;
        }
        if (type == "Camion") {
            QFont font("Arial", 10, QFont::Thin);
            font.setCapitalization(QFont::AllUppercase);
            return font;
        }
        if (type == "Moto") {
            QFont font("Arial", 10, QFont::Thin);
            font.setCapitalization(QFont::AllUppercase);
            return font;
        }
    }

    return QVariant();
}

/*
 * Inserisce 'count' nuove righe nel modello a partire dall'elemento di indice 'begin'
 */
bool QListModelAdapter::insert(Veicolo* v,int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1);
    modello->add(v);
    endInsertRows();
    return true;
}

bool QListModelAdapter::modify(Veicolo* v,int index){
    modello->replace(index,v);
    return true;
}

/*
 * Rimuove 'count' righe dal modello dei dati a partire dall'indice 'begin'
 */
bool QListModelAdapter::removeRows(int begin, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, begin, begin + count - 1);
    modello->remove(begin);
    endRemoveRows();
    return true;
}

/*
 * Salva il modello su file XML
 */
void QListModelAdapter::saveToFile() const {
    modello->saveToFile();
}

/*
 * Carica il modello in memoria leggendo i veicoli dal file XML
 */
void QListModelAdapter::loadFromFile() {
    modello->loadFromFile();
}

Modello* QListModelAdapter::getModello() const {
    return modello;
}

const Veicolo* QListModelAdapter::getcar(const QModelIndex& index)const{
    return modello->getVeicolo(index.row());
}

void QListModelAdapter::cancella(){
    for(int i=0; i<modello->contaVeicolo();i++)
        if(!modello->getVeicolo(i)->controllaTarga())
            removeRows(i,1);
}
