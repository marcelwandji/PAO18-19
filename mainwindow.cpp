#include "mainwindow.h"
#include "modello.h"
#include "editauto.h"
#include "editcamion.h"
#include "editmoto.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
    proxymodel(new QFilterProxyModel(this)),
    model(new QListModelAdapter(this)),
    view(new ListView(this)),
    searchbar(new QLineEdit(this)), editauto(new EditAuto(this,this)),
    editcamion(new EditCamion(this,this)), editmoto(new EditMoto(this,this)), number(new QLCDNumber()){

    setWindowTitle(tr("Qontainer")); // titolo applicazione
   // setWindowIcon(QIcon(":/images/veicolo.png")); // icona del programma

    // avvia caricamento del modello
    loadData();

    // fornisce alla view il modello dei dati che deve riflettere
    proxymodel->setSourceModel(model);
    view->setModel(proxymodel);

    searchbar->setPlaceholderText("Ricerca");

    // PULSANTI
    QPushButton* removeButton = new QPushButton("Rimuovi");
    QPushButton* clearSearchButton = new QPushButton("X");
    QPushButton* detailButton = new QPushButton("Dettagli");
    QPushButton* changeButton = new QPushButton("modifica");
    QPushButton* deleteButton = new QPushButton("clear errate");

    // Dà un nome al pulsante per usarlo nel css
    clearSearchButton->setObjectName("clearbutton");
    clearSearchButton->setToolTip("Clear search");

    // MENÙ e MENUBAR
    QMenuBar* menuBar = new QMenuBar();
    QMenu* menu = new QMenu("File", menuBar);
    QMenu* menu2= new QMenu("Agguingi",menuBar);
    QAction* saveAction = new QAction("Salva", menu);
    QAction* exitAction = new QAction("Esci", menu);
    QAction* autoAction = new QAction("Autovettura", menu2);
    QAction* camionAction = new QAction("Camion", menu2);
    QAction* motoAction = new QAction("Moto", menu2);

    // Setup del menù
    menuBar->addMenu(menu);
    menuBar->addMenu(menu2);
    menu->addAction(saveAction);
    menu->addAction(exitAction);
    menu2->addAction(autoAction);
    menu2->addAction(camionAction);
    menu2->addAction(motoAction);

    // LAYOUT
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Searchbar sottolayout
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchbar);
    searchLayout->addWidget(clearSearchButton);

    // Pulsanti sottolayout
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    buttonsLayout->addWidget(detailButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(changeButton);
    buttonsLayout->addWidget(deleteButton);
    QLabel* label = new QLabel("");
    number->display(model->getModello()->contaVeicolo());
    buttonsLayout->addWidget(label);
    buttonsLayout->addWidget(number);

    // Setup Main layout
    QVBoxLayout* primoLayout = new QVBoxLayout();
    primoLayout->addWidget(menuBar);
    primoLayout->addLayout(searchLayout);
    primoLayout->addWidget(view,0, Qt::AlignCenter);
    primoLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(primoLayout);

    // CONNECT
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveData()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeVeicolo()));
    connect(changeButton, SIGNAL(clicked()), this, SLOT(changeButtonClicked()));
    connect(detailButton, SIGNAL(clicked()), this, SLOT(detailVeicolo()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteTargheErrate()));
    connect(searchbar, SIGNAL(textChanged(QString)), this, SLOT(textFilterChanged()));
    connect(clearSearchButton, SIGNAL(clicked()), searchbar, SLOT(clear()));
    connect(autoAction, SIGNAL(triggered()), this, SLOT(autoButtonClicked()));
    connect(camionAction, SIGNAL(triggered()), this, SLOT(camionButtonClicked()));
    connect(motoAction, SIGNAL(triggered()), this, SLOT(motoButtonClicked()));

}

// NB: non distrugge i QWidget (di quello se ne occupa Qt)
MainWindow::~MainWindow() {}

QListModelAdapter* MainWindow::getModel() const
{
    return model;
}

/*
 * Ritorna la dimensione ottimale della finestra
 */
QSize MainWindow::sizeHint() const {
    return QSize(1000, 850);
}

// Scrive sul file
void MainWindow::saveData() {
    try {
        model->saveToFile();
    } catch (std::exception) {
        QMessageBox box(QMessageBox::Warning, "Errore di salvataggio",
                        "Non è stato possibile scrivere sul file", QMessageBox::Ok,this);
        box.exec();
    }
}

// Legge dal file
void MainWindow::loadData() {
    // in tale caso non serve passare per il proxymodel
    model->loadFromFile();
}

/* Aggiunge un nuovo Veicolo al modello e lo seleziona nella view */
void MainWindow::addVeicolo(Veicolo* v) {
    // effettua l'aggiunta di un veicolo sul modello dei dati
    proxymodel->insert(v,proxymodel->rowCount(), 1);
    // Dà focus all'ultimo elemento aggiunto (lo seleziona)
    view->clearSelection();
    view->selectionModel()->clearCurrentIndex();
    view->selectionModel()->select(proxymodel->index(model->rowCount() - 1, 0), QItemSelectionModel::Select);

    //Aggiorna il numero di elementi (veicoli) nella view
    number->display(model->getModello()->contaVeicolo());
}

/* Rimuove il veicolo selezionato nella view */
void MainWindow::removeVeicolo() {
    // prende l'elemento selezionato dalla view
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0){
        proxymodel->removeRows(selection.at(0).row(), 1);
        //Aggiorna il numero di elementi (veicoli) nella view
        number->display(model->getModello()->contaVeicolo());
    }
    else {
        QMessageBox box(QMessageBox::Information, "Nessun Elemento Selezionato",
                        "seleziona un veicolo e clicca su 'Rimuovi' per rimuoverlo !!! ", QMessageBox::Ok,this);
        box.exec();
    }
}

void MainWindow::textFilterChanged() {
    QRegExp regex(searchbar->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
    proxymodel->setFilterRegExp(regex);
}

void MainWindow::autoButtonClicked(){
    editauto->exec();
}

void MainWindow::camionButtonClicked(){
    editcamion->exec();
}

void MainWindow::motoButtonClicked(){
    editmoto->exec();
}

/* Dà dettagli sul veicolo selezionato nella view */
void MainWindow::detailVeicolo(){

    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0){
        const Veicolo* v = proxymodel->getCar(selection.at(0));
        bool bl = v->controllaTarga();
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setWindowTitle(tr("Dettagli Veicolo"));
        try {
            if(bl) throw bl;
            string tp = v->tipoVeicolo();
            string gt = v->getTarga();

            msgBox->setIcon(QMessageBox::Icon(QMessageBox::Warning));
            msgBox->setText(QString::fromStdString(tp) + " con targa errata: " +
                            QString::fromStdString(gt).toUpper() + "\n" +
                            "Il veicolo deve essere cancellato");
        } catch (bool) {
            string st = v->veicoloString();

            msgBox->setIcon(QMessageBox::Icon(QMessageBox::Information));
            msgBox->setText(QString::fromStdString(st).toUpper());
        }
        msgBox->exec();
    }
    else {
        QMessageBox box(QMessageBox::Information, "Nessun Elemento Selezionato",
                        "seleziona un veicolo e clicca su 'Dettagli' per visualizzare i dettagli !!! ",
                        QMessageBox::Ok,this);
        box.exec();
    }
}

void MainWindow::modificaVeicolo(int i,Veicolo* v){
    proxymodel->modify(v,i);
}

void MainWindow::changeButtonClicked(){
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();

    if(selection.size() > 0){

        if(dynamic_cast<const AutoVettura*>(proxymodel->getCar(selection.at(0)))){
            const AutoVettura* v = static_cast<const AutoVettura*>(proxymodel->getCar(selection.at(0)));
            int i = model->getModello()->getPosizione(v);
            EditAuto* ea = new EditAuto(this,this,i);
            ea->exec();
        }

        if(dynamic_cast<const Camion*>(proxymodel->getCar(selection.at(0)))){
            const Camion* v = static_cast<const Camion*>(proxymodel->getCar(selection.at(0)));
            int i = model->getModello()->getPosizione(v);
            EditCamion* ec = new EditCamion(this,this,i);
            ec->exec();
        }

        if(dynamic_cast<const Moto*>(proxymodel->getCar(selection.at(0)))){
            const Moto* v = static_cast<const Moto*>(proxymodel->getCar(selection.at(0)));
            int i = model->getModello()->getPosizione(v);
            EditMoto* em = new EditMoto(this,this,i);
            em->exec();
        }

    }
}

void MainWindow::deleteTargheErrate(){
    model->cancella();
    number->display(model->getModello()->contaVeicolo());
}
