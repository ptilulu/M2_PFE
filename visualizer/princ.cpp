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

void Princ::on_exportOBJAction_triggered()
{
    /*
    Ui_Princ::statusBar->showMessage("Exportation en OBJ...");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en OBJ..."), "C://", tr("OBJ Files (*.obj)"));
    if(fileName.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), QString("Vous devez spécifier un nom de fichier!"));
        return;
    }

    QFile objFile(fileName);
    if(objFile.open(QIODevice::ReadWrite)){
        QTextStream stream(&objFile);

    }
    ui->statusBar->showMessage("Exportation en .OBJ terminée!");*/


/*
    //export in obj
    uint height = dem->getHeight(),width =dem->getWidth();
    float x=-(width/2.0f) + 0.5f,z=-(height/2.0f) + 0.5f;
    for(uint l=0;l<height;l++){
        for(uint w=0;w<width;w++){
            stream << "v " << x << " " << dem->elevation_map[l*width+w] << " " << z << endl ;
            x++;
        }
        x=-(width/2.0f) + 0.5f;
        z++;
    }
    uint id=1;
    for(uint l=0;l<height-1;l++){
        for(uint w=0;w<width-1;w++){
            stream << "f " << id << " " << id+1 << " " << id+width+1 << " " << id+width << endl ;
            id++;
        }
        id++;
    }
*/
}

