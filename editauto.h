#ifndef EDITAUTO_H
#define EDITAUTO_H

#include "mainwindow.h"
#include <QComboBox>

class EditAuto : public QDialog
{
    //Q_OBJECT
private:
    int modifica;
    QLineEdit* tag1;
    QLineEdit* tag2;
    QComboBox* com;
    QLineEdit* tag4;
    QComboBox* box;
    MainWindow* view;

public:
    explicit EditAuto(MainWindow* v = nullptr,QWidget* parent = nullptr,int =-1);
    ~EditAuto(){}

private slots:
    void accept();

};

#endif // EDITAUTO_H
