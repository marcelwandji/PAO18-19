#include "modello.h"
#include "salva.h"

Modello::Modello() {}

Modello::~Modello() {
    for (Container<Veicolo*>::iterator it = lista.begin(); it != lista.end(); it++)
        delete *it; // cancella tutti i puntatori contenuti nella lista
}

// Metodo di salvataggio della lista nel file indicato
void Modello::saveToFile() const {
    XmlIO xmlio("../Qontainer/data.xml");
    xmlio.write(lista);
}

// Metodo di caricamento della lista dal file indicato
void Modello::loadFromFile() {
    XmlIO xmlio("../Qontainer/data.xml");
    lista = xmlio.read();
}

int Modello::contaVeicolo() const {
    return lista.size();
}

// Metodo per aggiungere un elemento alla lista
void Modello::add(Veicolo* v)
{
    bool esiste = false;
    for(auto it = lista.begin(); !esiste && it != lista.end(); it++)
        if((*it)->getTarga() == v->getTarga())
            esiste = true;

    if(!esiste) lista.insert(v);
}

// Metodo per togliere un elemento
void Modello::remove(int x) {
    delete lista[x];
    lista.remove(lista[x]);
}

// Ritorna l'elemento di indice i
const Veicolo* Modello::getVeicolo(int i) const{
    return lista[i];
}

void Modello::replace(int index, Veicolo* v) {
    delete lista.at(index);
    lista.replace(index, v);
}

int Modello::getPosizione(const Veicolo* v) const{
    int i =0;
    for(auto it = lista.begin(); (v!=*it) && it != lista.end(); it++)
        i++;
    return i;
}
