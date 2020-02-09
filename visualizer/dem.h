#ifndef DEM_H
#define DEM_H

#include <QString>
#include "gdal/gdal_priv.h"
#include <QDebug>
#include <QColor>
#include <QProgressBar>

class DEM
{
public:
    DEM(QString fileName);
    void initializeColorMap();

    float getElevationAt(int x, int y);
    QColor getColorFromElevation(float elevation);
    unsigned int getWidth();
    unsigned int getHeight();
    float getMaxElevation();
    float getMinElevation();
private:
    std::vector<std::pair<int, QColor>> color_map;
    std::vector<float> elevation_map;
    unsigned width;
    unsigned height;
};

#endif // DEM_H
