#include "princ.h"
#include <QDebug>
#include <QFileDialog>
#include <QProgressBar>
#include <QMessageBox>

Princ::Princ(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    this->setWindowTitle("Génération de terrains par DeepLearning");

    Ui_Princ::menuOuvrir->setIcon(QIcon(":/icons/open.png"));
    Ui_Princ::actionQuitter->setIcon(QIcon(":/icons/quit.png"));
    Ui_Princ::exportOBJAction->setIcon(QIcon(":/icons/obj.png"));
    Ui_Princ::actionCommandes->setIcon(QIcon(":/icons/commands.png"));
}

void Princ::on_actionQuitter_triggered()
{
    QApplication::quit();
}

void Princ::on_exportOBJAction_triggered()
{
    if(this->dem == nullptr) {
        QMessageBox::warning(this, tr("Erreur"), QString("Vous devez d'abord charger une image!"));
        return;
    }
    Ui_Princ::statusBar->showMessage("Exportation en OBJ...");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en OBJ..."), "C://", tr("OBJ Files (*.obj)"));
    if(fileName.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), QString("Vous devez spécifier un nom de fichier!"));
        return;
    }

    QFile objFile(fileName);
    if(objFile.open(QIODevice::ReadWrite)){
        QTextStream stream(&objFile);

        //export in obj
        uint height = dem->getHeight(), width =dem->getWidth();
        float x=-(width/2.0f) + 0.5f,z=-(height/2.0f) + 0.5f;
        for(uint l=0;l<height;l++){
            for(uint w=0;w<width;w++){
                stream << "v " << x*90 << " " << dem->getElevationAt(static_cast<int>(w),static_cast<int>(l)) << " " << z*90 << endl ;
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
    }
    Ui_Princ::statusBar->showMessage("Exportation en .OBJ terminée!");
}


void Princ::on_actionCommandes_triggered()
{
    if(commands != nullptr) commands->show();
    else {
        commands = new Commands;
        commands->show();
    }
}

void Princ::on_actionVoxel_triggered()
{
    this->glarea->setDisplayMode(GLArea::VOXEL);
    this->openFile();
}

void Princ::on_actionTerrain_triggered()
{
    this->glarea->setDisplayMode(GLArea::TERRAIN);
    this->openFile();
}

void Princ::openFile(){
    Ui_Princ::statusBar->showMessage("Sélection de l'image...");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir l'image de terrain..."), "C://", tr("ASCII (*.asc);;GeoTIFF (*.tif);;JPEG (*.jpg *.jpeg)"));
    if(fileName.isEmpty()) return;
    dem = new DEM(fileName);
    this->glarea->setDem(dem);
    QFileInfo fileInfo(fileName);
    Ui_Princ::statusBar->showMessage("Fichier " + fileInfo.baseName() + " ouvert avec succès!");
}
