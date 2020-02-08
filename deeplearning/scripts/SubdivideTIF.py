import os
from osgeo import gdal


def split(path):
    raw_file_name = os.path.splitext(os.path.basename(path))[0].replace("_downsample", "")

    tile_size_x = 60
    tile_size_y = 60

    ds = gdal.Open(path)
    band = ds.GetRasterBand(1)
    xsize = band.XSize
    ysize = band.YSize

    for i in range(0, xsize, tile_size_x):
        for j in range(0, ysize, tile_size_y):
            com_string = "gdal_translate -of GTIFF -srcwin " + str(i) + ", " + str(j) + ", " \
                         + str(tile_size_x) + ", " + str(tile_size_y) + " " + str(path) \
                         + " " + str("../downloaded/subdivided/") + str(raw_file_name) + "_" \
                         + str(i) + "_" + str(j) + ".tif"
            os.system(com_string)


if __name__ == "__main__":
    for file in os.listdir('../downloaded/tif'):
        if file.endswith(".tif"):
            split(os.path.join('../downloaded/tif', file))
