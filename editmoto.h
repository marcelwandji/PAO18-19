#ifndef EDITMOTO_H
#define EDITMOTO_H


#include "mainwindow.h"
#include <QComboBox>

class EditMoto : public QDialog
{
    //Q_OBJECT
private:
    int modifica;
    QLineEdit* tag1;
    QLineEdit* tag2;
    QComboBox* com;
    QLineEdit* tag4;
    QCheckBox* box;
    MainWindow* view;

public:
    explicit EditMoto(MainWindow*v = nullptr,QWidget* parent = nullptr,int =-1);
    ~EditMoto(){}

private slots:
    void accept();

};

#endif // EDITMOTO_H
