#ifndef AUTOVETTURA_H
#define AUTOVETTURA_H
#include "veicolo.h"

class AutoVettura : public Veicolo
{
private:
    int numeroPosti;
public:
    AutoVettura(std::string nt = "", std::string m="", std::string a="", std::string t="",int np=0 );
    int getNumeroPosti() const;
    std::string veicoloString() const;
    bool controllaTarga() const;
    std::string tipoVeicolo() const;
    bool operator==(const Veicolo& ) const;
};

#endif // AUTOVETTURA_H
