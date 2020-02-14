#include "princ.h"
#include <QDebug>
#include <QFileDialog>
#include <QProgressBar>

Princ::Princ(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    this->setWindowTitle("Génération de terrains par DeepLearning");
}

void Princ::on_actionOuvrir_triggered()
{
    Ui_Princ::statusBar->showMessage("Sélection de l'image tif");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir l'image de terrain..."), "C://", tr("GeoTIFF (*.tif);;JPEG (*.jpg *.jpeg)"));
    if(fileName.isEmpty()) return;
    dem = new DEM(fileName);
    this->glarea->setDem(dem);

    QFileInfo fileInfo(fileName);
    Ui_Princ::statusBar->showMessage("Fichier " + fileInfo.baseName() + " ouvert avec succès!");
}

void Princ::on_actionQuirer_triggered()
{
    QApplication::quit();
}
