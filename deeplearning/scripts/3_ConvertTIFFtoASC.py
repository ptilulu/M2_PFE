import os
from osgeo import gdal
import argparse


if __name__ == "__main__":
    if not os.path.exists("../downloaded/subdivided"):
        print("Subdivide folder not found! Creating...")
        os.makedirs("../downloaded/subdivided")
    for file in os.listdir("../downloaded/subdivided"):
        if file.endswith(".tif"):
        	fileasc=os.path.splitext(file)[0] +".asc"
        	com_string ="gdal_translate -of AAIGrid" + os.path.join(" ../downloaded/subdivided", file) + os.path.join(" ../downloaded/subdivided", fileasc)
        	os.system(com_string)
    for file in os.listdir('../downloaded/subdivided'):
        if file.endswith(".asc.aux.xml"):
        	os.remove("../downloaded/subdivided/" + file)
