#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistmodeladapter.h"
#include "listview.h"
#include "qfilterproxymodel.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QLayout>

#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QLCDNumber>

class EditAuto;
class EditCamion;
class EditMoto;
class Veicolo;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    QSize sizeHint() const override;
    void loadData(); // non è chiamata da un pulsante quindi non serve sia uno SLOT
    QListModelAdapter* getModel() const;

private:
    QFilterProxyModel* proxymodel;
    QListModelAdapter* model;
    ListView* view;
    QLineEdit* searchbar;
    EditAuto* editauto;
    EditCamion* editcamion;
    EditMoto* editmoto;
    QLCDNumber* number;

private slots:
    void saveData();
    void removeVeicolo();
    void detailVeicolo();
    void textFilterChanged();
    void autoButtonClicked();
    void camionButtonClicked();
    void motoButtonClicked();
    void changeButtonClicked();
    void deleteTargheErrate();

public slots:
    void addVeicolo(Veicolo*);
    void modificaVeicolo(int,Veicolo*);

};


#endif // MAINWINDOW_H
