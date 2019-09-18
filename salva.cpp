#include "salva.h"
#include "modello.h"

#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

XmlIO::XmlIO(QString filepath) : filename(filepath) {}

Container<Veicolo*> XmlIO::read() const {
    // Crea una lista
    Container<Veicolo*> list;

    // Apre un file (QFile)
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Non è stato possibile aprire il file" << file.errorString();
        return  list;
    }

    // Lettura da file XML
    QXmlStreamReader reader(&file); // QIODevice*
    if(reader.readNextStartElement()) {
        if(reader.name() == "root") {
            while(reader.readNextStartElement()) {
                if(reader.name() == "veicolo") {
                    // legge l'attributo 'type'
                    const QXmlStreamAttributes attributes = reader.attributes();
                    const QString type = attributes.hasAttribute("type") ? attributes.value("type").toString() : "";

                    reader.readNextStartElement();
                    // legge i campi del Veicolo contenuti nei tag

                    const QString t = reader.readElementText();
                    reader.readNextStartElement();

                    const QString m = reader.readElementText();
                    reader.readNextStartElement();

                    const QString a = reader.readElementText();
                    reader.readNextStartElement();

                    const QString tar = reader.readElementText();
                    reader.readNextStartElement();

                    const QString text = reader.readElementText();
                    reader.readNextStartElement();

                    // crea un nuovo veicolo con il tipo giusto e lo aggiunge alla lista
                    if(type == "Autovettura"){
                        list.insert(new AutoVettura(t.toStdString(),m.toStdString(),
                                                    a.toStdString(),tar.toStdString(),
                                                    text.toInt()));
                    }
                    if(type == "Camion"){
                        list.insert(new Camion(t.toStdString(),m.toStdString(),
                                                        a.toStdString(),tar.toStdString(),
                                                        text.toInt()));
                     }
                     if(type =="Moto"){
                            bool b = text == "si" ? true : false;
                            list.insert(new Moto(t.toStdString(),m.toStdString(),
                                                        a.toStdString(),tar.toStdString(),
                                                        b));
                     }
                    qDebug() << "Letto " + type +  "(telaio= " +t+ ",modello= " +m+ ",alimentazione= " +
                                a+ ",targa= " +tar+ ", special= " + text + ")";
                }
                else
                    reader.skipCurrentElement();
            }
        }
    }

    // Chiude il file e ritorna la lista con i Veicoli letti
    file.close();
    return list;
}

void XmlIO::write(const Container<Veicolo*>& lista) const {
    /* QSaveFile rispetto a QFile è più adatto per effettuare scritture su disco. Gestisce meglio
       i casi di errore, garantendo che non vengano persi i dati del file in caso di errori in scrittura */
    QSaveFile file(filename);

    // Apre un file. Se non si apre lancia una eccezione.
    if(!file.open(QIODevice::WriteOnly)) {
        throw std::exception();
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true); // Per leggibilità del file XML
    writer.writeStartDocument();    // Scrive le intestazioni XML
    writer.writeComment("File di salvataggio dell'applicazione. Non modificare a mano.");

    writer.writeStartElement("root");                                // <root>

    for(Container<Veicolo*>::iterator it = lista.begin(); it != lista.end(); it++) {
        writer.writeStartElement("veicolo");                            // <Veicolo>

        // Legge ogni campo dato del Veicolo
        const Veicolo* veicolo = *it;

        const std::string type = veicolo->tipoVeicolo();
        const std::string t = veicolo->getNumTelaio();
        const std::string m = veicolo->getModello();
        const std::string tar = veicolo->getTarga();
        const std::string a = veicolo->getAlimentazione();
        std::string  text;
        if(type == "Autovettura"){
            std::ostringstream ostr;
            ostr << (static_cast<AutoVettura*>(*it))->getNumeroPosti();
            text = ostr.str();
        }
        if(type == "Camion"){
            std::ostringstream ostr;
            ostr << (static_cast<Camion*>(*it))->getNumeroAssi();
            text = ostr.str();
        }
        if(type == "Moto"){
            bool gl = (static_cast<Moto*>(*it))->getGuidaLibera();
             text = gl ? "si" : "no";
        }

        writer.writeAttribute("type", QString::fromStdString(type)); // <veicolo type="valore">

        writer.writeStartElement("telaio");                  //<telaio>
        //writer.writeAttribute("telaio","");
        writer.writeCharacters(QString::fromStdString(t));   //...valore di t...
        writer.writeEndElement();                            //</telaio>

        writer.writeStartElement("modello");                 //<modello>
        //writer.writeAttribute("model","");
        writer.writeCharacters(QString::fromStdString(m));   //...valore di m...
        writer.writeEndElement();                            //</modello>

        writer.writeStartElement("alimentazione");           //<alimentazione>
        //writer.writeAttribute("alimentazione","");
        writer.writeCharacters(QString::fromStdString(a));   //...valore di a...
        writer.writeEndElement();                            //</alimentazione>

        writer.writeStartElement("targa");                   //<targa>
        //writer.writeAttribute("targa","");
        writer.writeCharacters(QString::fromStdString(tar)); //...valore di tar...
        writer.writeEndElement();                            //</targa>

        writer.writeStartElement("text");                    //<text>
       // writer.writeAttribute("text","");
        writer.writeCharacters(QString::fromStdString(text));//...valore di text...
        writer.writeEndElement();                            //</text>


        writer.writeEndElement(); // </veicolo>
        if (writer.hasError()) // se c'è stato un problema in scrittura interrompe ed esce
            throw std::exception();
    }

    writer.writeEndElement();                                        // </root>
    writer.writeEndDocument();  // chiude eventuali tag lasciati aperti e aggiunge una riga vuota alla fine

    file.commit(); // Scrive il file temporaneo su disco
}
