#include "dem.h"

DEM::DEM(QString fileName)
{
    GDALAllRegister();
    poDataset = (GDALDataset *) GDALOpen(fileName.toStdString().c_str(), GA_ReadOnly );
    if(poDataset == NULL) qDebug() << "Can't open file!" << fileName;
    else qDebug() << "Loaded! Size is" << poDataset->GetRasterXSize() << "x" << poDataset->GetRasterYSize() << "x" << poDataset->GetRasterCount();
    this->initializeColorMap();
}

void DEM::initializeColorMap()
{
    color_map.push_back(std::make_pair(-1, QColor(0, 0, 255)));
    color_map.push_back(std::make_pair(0, QColor(65, 194, 60)));
    color_map.push_back(std::make_pair(75, QColor(124, 208, 68)));
    color_map.push_back(std::make_pair(150, QColor(182, 223, 77)));
    color_map.push_back(std::make_pair(225, QColor(213, 230, 53)));
    color_map.push_back(std::make_pair(300, QColor(244, 237, 30)));
    color_map.push_back(std::make_pair(450, QColor(246, 219, 30)));
    color_map.push_back(std::make_pair(600, QColor(249, 201, 29)));
    color_map.push_back(std::make_pair(1000, QColor(249, 168, 14)));
    color_map.push_back(std::make_pair(1500, QColor(249, 134, 0)));
    color_map.push_back(std::make_pair(2250, QColor(203, 95, 62)));
    color_map.push_back(std::make_pair(3000, QColor(157, 56, 125)));
    color_map.push_back(std::make_pair(4500, QColor(186, 109, 170)));
    color_map.push_back(std::make_pair(6000, QColor(215, 162, 214)));
    color_map.push_back(std::make_pair(7500, QColor(230, 200, 230)));
}

int DEM::getElevationAt(int x, int y)
{
    GDALRasterBand  *poBand;
    int             nBlockXSize, nBlockYSize;
    int             bGotMin, bGotMax;
    double          adfMinMax[2];
    poBand = poDataset->GetRasterBand(1);
    poBand->GetBlockSize( &nBlockXSize, &nBlockYSize );

    adfMinMax[0] = poBand->GetMinimum( &bGotMin );
    adfMinMax[1] = poBand->GetMaximum( &bGotMax );
    if(!(bGotMin && bGotMax)) GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);

    float *pafScanline;
    int   nXSize = poBand->GetXSize();

    pafScanline = (float *) CPLMalloc(sizeof(float)*nXSize);
    CPLErr err = poBand->RasterIO( GF_Read, x, y, 1, 1,
                      pafScanline, nXSize, 1, GDT_Float32,
                      0, 0 );

    return pafScanline[0];
}

QColor DEM::getColorFromElevation(int elevation)
{
    for(unsigned int i = 0; i < color_map.size(); i++){
        if(elevation > color_map[i].first) continue;
        return color_map[i].second;
    }
    return color_map[color_map.size()-1].second;
}

int DEM::getWidth()
{
    return poDataset->GetRasterXSize();
}

int DEM::getHeight()
{
    return poDataset->GetRasterYSize();
}
