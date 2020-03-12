import os
from osgeo import gdal
import argparse


def split(path, width, height):
    raw_file_name = os.path.splitext(os.path.basename(path))[0].replace("_downsample", "")
    ds = gdal.Open(path)
    band = ds.GetRasterBand(1)

    for i in range(0, band.XSize, width):
        for j in range(0, band.YSize, height):
            com_string = "gdal_translate -of GTIFF -srcwin " + str(i) + ", " + str(j) + ", " \
                         + str(width) + ", " + str(height) + " " + str(path) \
                         + " " + str("../downloaded/subdivided/") + str(raw_file_name) + "_" \
                         + str(i) + "_" + str(j) + ".tif"
            os.system(com_string)


if __name__ == "__main__":
    if not os.path.exists("../downloaded/subdivided"):
        print("Subdivide folder not found! Creating...")
        os.makedirs("../downloaded/subdivided")
    parser = argparse.ArgumentParser()
    parser.add_argument("--width", type=int, default=600, help="Image width")
    parser.add_argument("--height", type=int, default=600, help="Image height")
    opt = parser.parse_args()
    for file in os.listdir('../downloaded/tif'):
        if file.endswith(".tif"):
            split(os.path.join('../downloaded/tif', file), opt.width, opt.height)
