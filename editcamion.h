#ifndef EDITCAMION_H
#define EDITCAMION_H


#include "mainwindow.h"
#include <QComboBox>

class EditCamion : public QDialog
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
    explicit EditCamion(MainWindow* v = nullptr,QWidget* parent = nullptr,int =-1);
    ~EditCamion(){}

private slots:
    void accept();

};

#endif // EDITCAMION_H
