import os
from osgeo import gdal


def split(path):
    raw_file_name = os.path.splitext(os.path.basename(path))[0].replace("_downsample", "")

    tile_size_x = 576
    tile_size_y = 576

    ds = gdal.Open(path)
    band = ds.GetRasterBand(1)
    xsize = band.XSize
    ysize = band.YSize

    com_string = " gdalwarp -ts " + str(tile_size_x) + " " + str(tile_size_y) + " " + str(path) \
                         + " " + str("../downloaded/resized/") + str(raw_file_name) + ".tif"
    os.system(com_string)


if __name__ == "__main__":
    for file in os.listdir('../downloaded/subdivided'):
        if file.endswith(".tif"):
            split(os.path.join('../downloaded/subdivided', file))