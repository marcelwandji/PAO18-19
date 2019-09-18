#include "editauto.h"
#include "autovettura.h"

EditAuto::EditAuto(MainWindow* v,QWidget* parent,int mod) : QDialog(parent),modifica(mod),
    tag1(new QLineEdit(this)),
    tag2(new QLineEdit(this)),
    com(new QComboBox(this)),
    tag4(new QLineEdit(this)),
    box (new QComboBox(this)),
    view(v){

    setWindowTitle(tr("AutoVettura"));

    QHBoxLayout* hl = new QHBoxLayout(this);
    QLabel*  a = new QLabel("Telaio");
    QLabel*  b = new QLabel("Modello");
    QLabel*  c = new QLabel("Alimentazione");
    QLabel*  d = new QLabel("Targa");
    QLabel*  e = new QLabel("Numero posti");

    box->addItem("2");
    box->addItem("4");
    box->addItem("5");
    box->addItem("6");
    box->addItem("7");
    box->addItem("8");
    box->addItem("9");

    com->addItem("Benzina");
    com->addItem("Gasolio");
    com->addItem("Metano");
    com->addItem("GPL");

    if(modifica >=0){
        tag1->setText(QString::fromStdString(view->getModel()->getModello()->getVeicolo(modifica)->getNumTelaio()));
        tag2->setText(QString::fromStdString(view->getModel()->getModello()->getVeicolo(modifica)->getModello()));
        tag4->setText(QString::fromStdString(view->getModel()->getModello()->getVeicolo(modifica)->getTarga()));

        com->setCurrentText((QString::fromStdString(view->getModel()->getModello()->getVeicolo(modifica)->getAlimentazione())));
        box->setCurrentText((QString::number(static_cast<const AutoVettura*>(view->getModel()->getModello()->getVeicolo(modifica))->getNumeroPosti())));

    }

    QPushButton* B1 = new QPushButton("Aggiungi",this);
    QPushButton* B2 = new QPushButton("Quit",this);

    QHBoxLayout* h2 = new QHBoxLayout();
    QHBoxLayout* h3 = new QHBoxLayout();
    QHBoxLayout* h4 = new QHBoxLayout();
    QHBoxLayout* h5 = new QHBoxLayout();
    QHBoxLayout* h6 = new QHBoxLayout();

    h2->addWidget(a); h2->addWidget(tag1);
    h3->addWidget(b); h3->addWidget(tag2);
    h4->addWidget(c); h4->addWidget(com);
    h5->addWidget(d); h5->addWidget(tag4);
    h6->addWidget(e); h6->addWidget(box);

    QVBoxLayout* hm = new QVBoxLayout();
    QVBoxLayout* hv = new QVBoxLayout();


    hl->addLayout(hm);
    hl->addLayout(hv);

    hm->addLayout(h2);
    hm->addLayout(h3);
    hm->addLayout(h4);
    hm->addLayout(h5);
    hm->addLayout(h6);

    hv->addWidget(B1);
    hv->addWidget(B2);

    connect(B1, SIGNAL(clicked()), this, SLOT(accept()));
    connect(B2, SIGNAL(clicked()), this, SLOT(close()));

}

void EditAuto::accept() {
    if(!tag1->text().isEmpty() && !tag2->text().isEmpty() &&
        !tag4->text().isEmpty()){

        int c = box->currentText().toInt();
        std::string m = com->currentText().toStdString();
       AutoVettura* A= new AutoVettura(tag1->text().toStdString(),tag2->text().toStdString(),
                                            m,tag4->text().toStdString(),c);

       tag1->clear(); tag2->clear(); tag4->clear();
       if(modifica < 0) view->addVeicolo(A);
       else view->modificaVeicolo(modifica,A);
       close();

        }
    else {
            //QMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text, StandardButtons buttons = NoButton, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint)

            QMessageBox* msgBox = new QMessageBox(this);
            msgBox->setIcon(QMessageBox::Icon(QMessageBox::Warning));
            msgBox->setWindowTitle(tr("Informazioni mancanti"));
            msgBox->setText("Controllare se non ci sono campi vuoti !!!");
            msgBox->exec();
    }
}
