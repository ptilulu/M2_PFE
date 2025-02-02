import requests
import os

# FIRST SCRIPT: RETRIEVE DATA FROM WEB
if __name__ == "__main__":
    if not os.path.exists("../downloaded/zip"):
        print("Download folder not found! Creating...")
        os.makedirs("../downloaded/zip")

    print("Starting retrieving data from SRTM...")
    for i in range(1, 73):
        for j in range(1, 25):
            if os.path.isfile("../downloaded/zip/srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2))):
                print("[Available] srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2)))
            else:
                response = requests.get(
                    "http://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/srtm_{}_{}.zip".format(
                        str(i).zfill(2),
                        str(j).zfill(2)
                    )
                )
                if response.status_code == 200:
                    file_name = "srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2))
                    file_path = "../downloaded/zip/" + file_name
                    with open(file_path, 'wb') as f:
                        print("[Downloaded]: " + file_name)
                        f.write(response.content)
                else:
                    print("[Not Found] srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2)))
