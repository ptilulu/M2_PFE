import os


def process(path):
    raw_file_name = os.path.splitext(os.path.basename(path))[0].replace("_downsample", "")
    com_string = "gdal_translate -b 1 " + str(path) + " " + \
                 str("../data/dcgan/generated/processed/") + str(raw_file_name) + ".tif"
    print(com_string)
    os.system(com_string)
    com_string = "gdal_translate -of AAIGrid " + str("../data/dcgan/generated/processed/") + str(raw_file_name) + ".tif " + \
                 str("../data/dcgan/generated/processed/") + str(raw_file_name) + ".asc"
    os.system(com_string)


if __name__ == "__main__":
    for file in os.listdir('../data/dcgan/generated/'):
        if file.endswith(".tif"):
            process(os.path.join('../data/dcgan/generated', file))
    for file in os.listdir('../data/dcgan/generated/processed/'):
        if file.endswith(".xml"):
            os.remove(os.path.join('../data/dcgan/generated/processed/', file))
