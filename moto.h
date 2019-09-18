#ifndef MOTO_H
#define MOTO_H
#include "veicolo.h"

class Moto : public Veicolo
{
private:
    bool guidaLibera;
public:
    Moto(std::string nt = "", std::string m="", std::string a="", std::string t="",bool gl=false);
    bool getGuidaLibera() const;
    std::string veicoloString() const;
    bool controllaTarga() const;
    std::string tipoVeicolo() const;
    bool operator==(const Veicolo& ) const;
};

#endif // MOTO_H
