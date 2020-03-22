from osgeo import gdal
import argparse
import os


def isUseless(path):
    dataset = gdal.Open(path, gdal.GA_ReadOnly)
    if dataset:
        band = dataset.GetRasterBand(1)
        min = band.GetMinimum()
        max = band.GetMaximum()
        if not min or not max:
            (min, max) = band.ComputeRasterMinMax(True)
        del dataset
        if max == float(32767):
            print("Useless image: Removing " + path)
            os.remove(path)
            return True
    else:
        print("Error: Cannot open file " + path)
    return False


if __name__ == "__main__":
    for file in os.listdir('../downloaded/subdivided/'):
        if file.endswith(".tif"):
            isUseless(os.path.join('../downloaded/subdivided/', file))
