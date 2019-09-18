#ifndef VEICOLO_H
#define VEICOLO_H
#include <sstream>
#include <string>

class Veicolo {

private:
    std::string numTelaio;
    std::string modello;
    std::string alimentazione;
protected:
    std::string targa;

public:
    Veicolo(std::string, std::string, std::string, std::string);
    std::string getNumTelaio() const;
    std::string getModello() const;
    std::string getTarga() const;
    std::string getAlimentazione() const;
    virtual std::string veicoloString() const;
    virtual bool controllaTarga() const =0;
    virtual std::string tipoVeicolo() const =0;
    virtual bool operator==(const Veicolo& ) const;
    virtual ~Veicolo();
};

#endif // VEICOLO_H
