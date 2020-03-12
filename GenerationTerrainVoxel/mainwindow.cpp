#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOuvrir_une_image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir l'image de terrain..."), "C://", tr("GeoTIFF (*.tif);;JPEG (*.jpg *.jpeg)"));
    if(fileName.isEmpty()) return;
    dem = new DEM(fileName);
    ui->glarea->setDem(dem);

    QFileInfo fileInfo(fileName);
}
