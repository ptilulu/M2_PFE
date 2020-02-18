// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#ifndef PRINC_H
#define PRINC_H

#include "ui_princ.h"
#include "dem.h"

class Princ : public QMainWindow, private Ui::Princ
{
    Q_OBJECT

public:
    explicit Princ(QWidget *parent = nullptr);
private:
    DEM* dem = nullptr;
private slots:
    void on_actionOuvrir_triggered();
    void on_actionQuirer_triggered();
    void on_exportOBJAction_triggered();
};

#endif // PRINC_H
