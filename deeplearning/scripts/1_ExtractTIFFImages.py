import os
import fnmatch
import zipfile

# SECOND SCRIPT: EXTRACT DATA
if __name__ == "__main__":
    if not os.path.exists("../downloaded/tif"):
        print("TIF folder not found! Creating...")
        os.makedirs("../downloaded/tif")

    print("Starting extraction from ZIP files...")
    for root, dirs, files in os.walk('../downloaded/zip'):
        for filename in fnmatch.filter(files, '*.zip'):
            if os.path.isfile(os.path.join('../downloaded/tif/', os.path.splitext(filename)[0] + '.tif')):
                continue
            with zipfile.ZipFile(os.path.join(root, filename)) as zf:
                [zf.extract(file, r"../downloaded/tif") for file in zf.namelist() if file.endswith('.tif')]
