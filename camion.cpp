#include "camion.h"

Camion::Camion(std::string nt, std::string m, std::string a, std::string t, int na):
    Veicolo(nt,m,a,t), numeroAssi(na) {}

int Camion::getNumeroAssi() const
{
    return numeroAssi;
}

std::string Camion::veicoloString() const
{
    std::ostringstream ostr;
        ostr << numeroAssi;
    return tipoVeicolo()+ "\n" + Veicolo::veicoloString() + "Numero assi = " + ostr.str();
}

bool Camion::controllaTarga() const
{  // [ XA 000 AA ] => targa valida di un camion
    char x =  targa.at(0);
    x = char(toupper(x));
    if(targa.length() == 7 &&
        x == 'X' && isalpha(targa.at(1)) &&
           isdigit(targa.at(2)) && isdigit(targa.at(3)) &&
              isdigit(targa.at(4)) && isalpha(targa.at(5)) &&
                 isalpha(targa.at(6))) return true;
    return false;
}

std::string Camion::tipoVeicolo() const {
    return "Camion";
}

bool Camion::operator==(const Veicolo& v) const
{
    return dynamic_cast<const Camion*>(&v) && Veicolo::operator==(v) &&
            numeroAssi == static_cast<const Camion&>(v).numeroAssi;
}
