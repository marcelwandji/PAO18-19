#include "moto.h"

Moto::Moto(std::string nt, std::string m, std::string a, std::string t, bool gl) :
    Veicolo(nt,m,a,t), guidaLibera(gl) {}

bool Moto::getGuidaLibera() const
{
    return guidaLibera;
}

std::string Moto::veicoloString() const
{
    return tipoVeicolo()+ "\n" + Veicolo::veicoloString() + "Guida libera = " + (guidaLibera ? "Si" : "No");
}

bool Moto::controllaTarga() const
{// (ED 99 999) => targa moto valide;
    if(targa.length() == 7 &&
        isalpha(targa.at(0)) && isalpha(targa.at(1)) &&
           isdigit(targa.at(2)) && isdigit(targa.at(3)) &&
              isdigit(targa.at(4)) && isdigit(targa.at(5)) &&
                 isdigit(targa.at(6))) return true;
    return false;
}

std::string Moto::tipoVeicolo() const {
    return "Moto";
}

bool Moto::operator==(const Veicolo& v) const
{
    return dynamic_cast<const Moto*>(&v) && Veicolo::operator==(v) &&
            guidaLibera == static_cast<const Moto&>(v).guidaLibera;
}
