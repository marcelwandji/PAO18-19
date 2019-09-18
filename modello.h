#ifndef MODELLO_H
#define MODELLO_H
#include "autovettura.h"
#include "camion.h"
#include "moto.h"
#include "container.cpp"

using std::string;

class Modello {
private:
    Container<Veicolo*> lista;
public:
    Modello();
    ~Modello();

    void saveToFile() const; // scrive sul file
    void loadFromFile();     // legge dal file
    int contaVeicolo() const; // conta i veicoli nella lista
    void replace(int, Veicolo*); // sostituisce il veicolo di indice specificato con un altro
    void add(Veicolo*); // aggiunge un Veicolo alla lista
    void remove(int); // rimuove il Veicolo di indice 'index'
    const Veicolo* getVeicolo(int) const; // ritorna il Veicolo di indice specificato
    int getPosizione(const Veicolo*) const;

};


#endif // MODELLO_H
