#ifndef SALVA_H
#define SALVA_H

#include <QString>
#include "container.h"

class Veicolo;
class XmlIO {
private:
    QString filename;
public:
    XmlIO(QString);
    Container<Veicolo*> read() const;
    void write(const Container<Veicolo*>&) const;
};

#endif // SALVA_H
