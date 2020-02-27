#ifndef DEM_H
#define DEM_H

#include <QString>
#include "gdal/gdal_priv.h"
#include <QDebug>
#include <QColor>
#include <QProgressBar>
#include <QFileInfo>

class DEM
{
public:
    DEM(QString fileName);
    void initializeColorMap();

    void fromGeotif(QString fileName);
    void fromAscii();
    void fromJpeg(QString fileName);
    void parseASCII(QString fileName);

    float getElevationAt(int x, int y);
    QColor getColorFromElevation(float elevation);
    unsigned int getWidth();
    unsigned int getHeight();
    float getMaxElevation();
    float getMinElevation();
    std::vector<float> elevation_map;
private:
    std::vector<std::pair<int, QColor>> color_map;
    unsigned width = 0;
    unsigned height = 0;
};

#endif // DEM_H
