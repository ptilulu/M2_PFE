#ifndef DEM_H
#define DEM_H

#include <QString>
#include <QDebug>
#include <QColor>
#include <QProgressBar>
#include <QFileInfo>
#include <QMessageBox>

#include "gdal/gdal_priv.h"

/**
 * @brief La classe DEM utilisée pour récupérer les données d'élévation depuis les différents fichiers d'entrée
 */
class DEM
{
    public:
        /**
         * @brief DEM Constructeur
         * @param fileName Chemin vers le fichier d'entrée
         */
        DEM(QString fileName);

        /**
         * @brief fromGeotif Récupère les données d'élévation depuis un fichier TIFF
         * @param fileName Chemin vers le fichier d'entrée
         */
        void fromGeotif(QString fileName);

        /**
         * @brief fromAscii Récupère les données d'élévation depuis un fichier ASC
         * @param fileName Chemin vers le fichier d'entrée
         */
        void fromAscii(QString fileName);

        /**
         * @brief fromJpeg Récupère les données d'élévation depuis un fichier JPEG
         * @param fileName Chemin vers le fichier d'entrée
         */
        void fromJpeg(QString fileName);

        /**
         * @brief getElevationAt Récupère l'élévation au point (x, y)
         * @param x
         * @param y
         * @return Elevation au point (x,y)
         */
        float getElevationAt(int x, int y);

        /**
         * @brief getWidth Renvoie la largeur du DEM
         * @return Largeur du DEM
         */
        unsigned int getWidth();

        /**
         * @brief getHeight Renvoie la hauteur du DEM
         * @return Hauteur du DEM
         */
        unsigned int getHeight();

        /**
         * @brief getElevationMap Renvoie le tableau d'élévation
         * @return Tableau d'élévation
         */
        std::vector<float> getElevationMap();

        /**
         * @brief getMaxElevation Renvoie l'élévation maximale du DEM
         * @return Valeur maximale d'élévation du DEM
         */
        float getMaxElevation();

        /**
         * @brief getMinElevation Renvoie l'élévation minimale du DEM
         * @return Valeur minimale d'élévation du DEM
         */
        float getMinElevation();

    private:

        /**
         * @brief width Largeur du DEM
         */
        unsigned int width = 0;

        /**
         * @brief height Hauteur du DEM
         */
        unsigned height = 0;

        /**
         * @brief maxElevation Elevation maximale du DEM
         */
        float maxElevation = 0;

        /**
         * @brief minElevation Elevation minimale du DEM
         */
        float minElevation = 0;

        /**
         * @brief elevation_map Tableau 3D contennant les données d'élévation de terrain
         */
        std::vector<float> elevation_map;
};

#endif // DEM_H
