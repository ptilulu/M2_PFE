from osgeo import gdal
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-filename", type=str, help="File info")
    opt = parser.parse_args()
    dataset = gdal.Open(opt.filename, gdal.GA_ReadOnly)
    if dataset:
        print("Driver: {}/{}".format(dataset.GetDriver().ShortName,
                                     dataset.GetDriver().LongName))
        print("Size is {} x {} x {}".format(dataset.RasterXSize,
                                            dataset.RasterYSize,
                                            dataset.RasterCount))
        print("Projection is {}".format(dataset.GetProjection()))
        geotransform = dataset.GetGeoTransform()
        if geotransform:
            print("Origin = ({}, {})".format(geotransform[0], geotransform[3]))
            print("Pixel Size = ({}, {})".format(geotransform[1], geotransform[5]))

        band = dataset.GetRasterBand(1)
        print("Band Type={}".format(gdal.GetDataTypeName(band.DataType)))

        min = band.GetMinimum()
        max = band.GetMaximum()
        if not min or not max:
            (min,max) = band.ComputeRasterMinMax(True)
        print("Min={:.3f}, Max={:.3f}".format(min,max))

        if band.GetOverviewCount() > 0:
            print("Band has {} overviews".format(band.GetOverviewCount()))

        if band.GetRasterColorTable():
            print("Band has a color table with {} entries".format(band.GetRasterColorTable().GetCount()))
        del dataset
