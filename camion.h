#ifndef CAMION_H
#define CAMION_H
#include "veicolo.h"

class Camion : public Veicolo
{
private:
    int numeroAssi;
public:
    Camion(std::string nt = "", std::string m="", std::string a="", std::string t="",int na=0);
    int getNumeroAssi() const;
    std::string veicoloString() const;
    bool controllaTarga() const;
    std::string tipoVeicolo() const;
    bool operator==(const Veicolo& ) const;
};


#endif // CAMION_H
