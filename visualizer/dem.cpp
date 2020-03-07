#include "dem.h"

/**
 * @brief DEM::DEM
 * @param fileName
 */
DEM::DEM(QString fileName)
{
    QFileInfo fileInfo(fileName);
    if(fileInfo.suffix() == "tif") fromGeotif(fileName);
    else if(fileInfo.suffix() == "asc" ) fromAscii(fileName);
    else if(fileInfo.suffix() == "jpg" || fileInfo.suffix() == "jpeg") fromJpeg(fileName);


    float maxElevation = -INT_MAX;
    float minElevation = INT_MAX;
    for(unsigned int i = 0; i < this->width; i++){
        for(unsigned int j = 0; j < this->height; j++){
            float currentElevation = this->getElevationAt(i, j);
            if(maxElevation < currentElevation) maxElevation = currentElevation;
            if(minElevation > currentElevation) minElevation = currentElevation;
        }
    }
    this->maxElevation = maxElevation;
    this->minElevation = minElevation;
    
    qDebug() << "DEM created! Size:" << this->width << "x" << this->height << "Min/Max" << this->minElevation << "/" << this->maxElevation;
}

/**
 * @brief DEM::fromGeotif
 * @param fileName
 */
void DEM::fromGeotif(QString fileName)
{
    // Initialize GDAL
    GDALAllRegister();

    // Open the file
    GDALDataset *dataset = (GDALDataset *) GDALOpen(fileName.toStdString().c_str(), GA_ReadOnly );
    if(dataset == NULL) qDebug() << "Can't open file!" << fileName;

    // Get image metadata
    this->width = dataset->GetRasterXSize();
    this->height = dataset->GetRasterYSize();

    // Get the raster band (DEM has one raster band representing elevation)
    GDALRasterBand *elevationBand = dataset->GetRasterBand(1);

    // Create an array of width*height 32-bit floats (~400MB memory)
    std::vector<float> data(width * height, 0.0f);
    this->elevation_map = data;

    // Read the entire file into the array
    elevationBand->RasterIO(GF_Read, 0, 0, this->width, this->height, &this->elevation_map[0], this->width, this->height, GDT_Float32, 0, 0);

    // Close the file
    GDALClose(dataset);

    // Setting right values
    for(unsigned int i = 0; i < this->width; i++)
    {
        for(unsigned int j = 0; j < this->height; j++)
        {
            // Water
            if(elevation_map[i + j * this->width] < 0) elevation_map[i + j * this->width] = 0;
        }
    }
}

/**
 * @brief DEM::fromAscii
 * @param fileName
 */
void DEM::fromAscii(QString fileName)
{
    // Open ASC file
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
    {
       qDebug("Could not open file");
       return;
    }

    // Variables
    QTextStream stream(&file);
    QString line;
    std::vector<std::vector<float>> elevation_map;

    // Reading the file
    while(!stream.atEnd())
    {
         line = stream.readLine();

         // Ignore useless lines
         if(line.startsWith("xllcorner") || line.startsWith("yllcorner") || line.startsWith("cellsize") || line.startsWith("NODATA_value")) continue;

         QStringList values = line.split(' ');
         values.removeAll(QString(""));

         // Get terrain size
         if(line.startsWith("ncols")) { this->height = values[1].toInt(); continue; }
         if(line.startsWith("nrows")) { this->width = values[1].toInt(); continue; }

         std::vector<float> vecTemp;
         foreach(QString str, values) vecTemp.push_back(str.toFloat());
         elevation_map.push_back(vecTemp);
    }

    // Closing file
    file.close();

    // vector<vector<float>> ==> vector<float> and scaling
    std::vector<float> data(this->width * this->height, 0.0f);
    this->elevation_map = data;

    for(unsigned int i = 0; i < this->width; i++)
    {
        for(unsigned int j = 0; j < this->height; j++)
        {
            // Water
            if(elevation_map[i][j] < 0) elevation_map[i][j] = 0;

            // Set and scale
            this->elevation_map[i * this->height + j] = elevation_map[i][j];
        }
    }
}


/**
 * @brief DEM::fromJpeg
 * @param fileName
 */
void DEM::fromJpeg(QString fileName)
{
    // Open JPG file
    QImage image(fileName);

    // Get terrain size
    this->width = image.width();
    this->height = image.height();

    std::vector<float> data(this->width * this->height, 0.0f);
    this->elevation_map = data;

    for(unsigned int i = 0; i < this->width; i++)
    {
        for(unsigned int j = 0; j < this->height; j++)
        {
            // Get pixel color
            QColor color = image.pixelColor(i, j);

            // Check if it's grey shade
            if(color.red() == color.blue() && color.red() == color.green())
                this->elevation_map[i + j * this->width] = color.red();
            else this->elevation_map[i + j * this->width] = 0;
        }
    }
}

/**
 * @brief DEM::getElevationAt
 * @param x
 * @param y
 * @return
 */
float DEM::getElevationAt(int x, int y)
{
    return this->elevation_map[x + y * this->width];
}

/**
 * @brief DEM::getNormalizedElevationAt
 * @param x
 * @param y
 * @return
 */
float DEM::getNormalizedElevationAt(int x, int y)
{
    return 100 * elevation_map[x + y * this->width] / this->maxElevation;
}

/**
 * @brief DEM::getWidth
 * @return
 */
unsigned int DEM::getWidth()
{
    return this->width;
}

/**
 * @brief DEM::getHeight
 * @return
 */
unsigned int DEM::getHeight()
{
    return this->height;
}

/**
 * @brief DEM::getElevationMap
 * @return
 */
std::vector<float> DEM::getElevationMap()
{
    return this->elevation_map;
}

/**
 * @brief DEM::getMaxElevation
 * @return
 */
float DEM::getMaxElevation()
{
    return this->maxElevation;
}

/**
 * @brief DEM::getMinElevation
 * @return
 */
float DEM::getMinElevation()
{
    return this->minElevation;
}
