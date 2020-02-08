#ifndef DEM_H
#define DEM_H

#include <QString>
#include "gdal/gdal_priv.h"
#include <QDebug>
#include <QColor>

class DEM
{
public:
    DEM(QString fileName);
    void initializeColorMap();
    int getElevationAt(int x, int y);
    QColor getColorFromElevation(int elevation);
    int getWidth();
    int getHeight();
private:
    GDALDataset *poDataset;
    std::vector<std::pair<int, QColor>> color_map;
};

#endif // DEM_H
