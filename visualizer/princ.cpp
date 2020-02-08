#include "princ.h"
#include <QDebug>
#include <QFileDialog>

Princ::Princ(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    this->setWindowTitle("Génération de terrains par DeepLearning");
}

void Princ::on_actionOuvrir_triggered()
{
    Ui_Princ::statusBar->showMessage("Sélection de l'image tif");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir l'image de terrain..."), "C://", tr("GeoTIFF Files (*.tif)"));
    if(fileName.isEmpty()) return;
    dem = new DEM(fileName);
    QFileInfo fileInfo(fileName);
    Ui_Princ::statusBar->showMessage("Fichier " + fileInfo.baseName() + " ouvert avec succès!");
    qDebug() << dem->getColorFromElevation(dem->getElevationAt(0, 0));
    qDebug() << dem->getColorFromElevation(dem->getElevationAt(5999, 5999));
}

void Princ::on_actionQuirer_triggered()
{
    QApplication::quit();
}
