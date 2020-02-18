#include "dem.h"

DEM::DEM(QString fileName)
{
    QFileInfo fileInfo(fileName);
    if(fileInfo.suffix() == "tif") fromGeotif(fileName);
    else if(fileInfo.suffix() == "jpg" || fileInfo.suffix() == "jpeg") fromJpeg(fileName);
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

void DEM::fromGeotif(QString fileName)
{
    // Initialize GDAL
    GDALAllRegister();

    // Open the file
    GDALDataset *dataset = (GDALDataset *) GDALOpen(fileName.toStdString().c_str(), GA_ReadOnly );
    if(dataset == NULL) qDebug() << "Can't open file!" << fileName;
    else qDebug() << "Loaded! Size is" << dataset->GetRasterXSize() << "x" << dataset->GetRasterYSize() << "x" << dataset->GetRasterCount();

    // Get image metadata
    this->width = dataset->GetRasterXSize();
    this->height = dataset->GetRasterYSize();


    // Get the raster band (DEM has one raster band representing elevation)
    GDALRasterBand  *elevationBand = dataset->GetRasterBand(1);

    // Create an array of width*height 32-bit floats (~400MB memory)
    std::vector<float> data(width * height, 0.0f);
    elevation_map = data;

    // Read the entire file into the array (you can change the options to read only a portion
    // of the file, or even scale it down if you want)

    qDebug() << "Loading array...";
    elevationBand->RasterIO(GF_Read, 0, 0, this->width, this->height, &this->elevation_map[0], this->width, this->height, GDT_Float32, 0, 0);
    qDebug() << "done";

    // Close the file
    GDALClose(dataset);
}
void DEM::fromJpeg(QString fileName)
{
    QImage image(fileName);
    this->width = image.width();
    this->height = image.height();

    std::vector<float> data(this->width * this->height, 0.0f);
    elevation_map = data;

    for(unsigned int i = 0; i < this->width; i++){
        for(unsigned int j = 0; j < this->height; j++){
            QColor color = image.pixelColor(i, j);
            if(color.red() == color.blue() && color.red() == color.green())
                elevation_map[i + j * this->width] = color.red();
            else {
                break;
                qDebug() << "Image is not in grey level";
            }
        }
    }

}

float DEM::getElevationAt(int x, int y)
{
    return elevation_map[x + y * this->width];
}

QColor DEM::getColorFromElevation(float elevation)
{
    for(unsigned int i = 0; i < color_map.size(); i++){
        if(elevation > color_map[i].first) continue;
        return color_map[i].second;
    }
    return color_map[color_map.size()-1].second;
}

unsigned int DEM::getWidth()
{
    return this->width;
}

unsigned int DEM::getHeight()
{
    return this->height;
}

float DEM::getMaxElevation()
{
    int maxElevation = -INT_MAX;
    for(unsigned int i = 0; i < this->width; i++){
        for(unsigned int j = 0; j < this->height; j++){
            float currentElevation = this->getElevationAt(i, j);
            if(maxElevation < currentElevation) maxElevation = currentElevation;
        }
    }
    return maxElevation;
}

float DEM::getMinElevation()
{
    int minElevation = INT_MAX;
    for(unsigned int i = 0; i < this->getWidth(); i++){
        for(unsigned int j = 0; j < this->getHeight(); j++){
            float currentElevation = this->getElevationAt(i, j);
            if(minElevation > currentElevation) minElevation = currentElevation;
        }
    }
    return minElevation;
}
