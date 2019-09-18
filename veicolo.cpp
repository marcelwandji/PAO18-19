#include "veicolo.h"

Veicolo::Veicolo(std::string nt, std::string m, std::string a, std::string t) : numTelaio(nt),
modello(m), alimentazione(a), targa(t){}

std::string Veicolo::getNumTelaio() const
{
    return numTelaio;
}

std::string Veicolo::getModello() const
{
    return modello;
}

std::string Veicolo::getTarga() const
{
    return targa;
}

std::string Veicolo::getAlimentazione() const
{
    return alimentazione;
}

std::string Veicolo::veicoloString() const
{
    return "Telaio = " + numTelaio + "\n" +
            "Modello = "+ modello + "\n" +
            "Alimentazione = " + alimentazione + "\n"
            "Targa = " + targa + "\n";
}

bool Veicolo::operator==(const Veicolo& v ) const
{
    return numTelaio == v.numTelaio && modello == v.modello && alimentazione == v.alimentazione
            && targa == v.targa;
}

Veicolo::~Veicolo() = default;












