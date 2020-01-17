import os
import fnmatch
import zipfile

def extractor(zip_file):
    extensions = ('.tif')
    [zip_file.extract(file, r"../downloaded/tif") for file in zip_file.namelist() if file.endswith(extensions)]


def extractTifFiles():
    if not os.path.exists("../downloaded/tif"):
        os.makedirs("../downloaded/tif")
    pattern = '*.zip'
    for root, dirs, files in os.walk('../downloaded'):
        for filename in fnmatch.filter(files, pattern):
            if os.path.isfile(os.path.join('../downloaded/tif/', os.path.splitext(filename)[0] + '.tif')):
                print(os.path.splitext(filename)[0] + '.tif trouvé')
                continue
            with zipfile.ZipFile(os.path.join(root, filename)) as zf:
                extractor(zf)
                print(filename, "extrait!")


if __name__ == "__main__":
    extractTifFiles()
