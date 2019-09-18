#include "autovettura.h"

AutoVettura::AutoVettura(std::string nt, std::string m, std::string a, std::string t,int np)
    : Veicolo(nt,m,a,t) , numeroPosti(np) {}

int AutoVettura::getNumeroPosti() const
{
    return numeroPosti;
}
std::string AutoVettura::veicoloString() const
{
    std::ostringstream ostr;
    ostr << numeroPosti;
    return tipoVeicolo() + "\n" + Veicolo::veicoloString() + "Numero posti = " + ostr.str();
}

bool AutoVettura::controllaTarga() const
{// [CZ 898 NF] => targa autovettura valida
    if(targa.length() == 7 &&
        isalpha(targa.at(0)) && isalpha(targa.at(1)) &&
           isdigit(targa.at(2)) && isdigit(targa.at(3)) &&
              isdigit(targa.at(4)) && isalpha(targa.at(5)) &&
                 isalpha(targa.at(6))) return true;
    return false;
}

std::string AutoVettura::tipoVeicolo() const {
    return "Autovettura";
}

bool AutoVettura::operator==(const Veicolo& v) const
{
    return dynamic_cast<const AutoVettura*>(&v) && Veicolo::operator==(v) &&
            numeroPosti == static_cast<const AutoVettura&>(v).numeroPosti;
}
