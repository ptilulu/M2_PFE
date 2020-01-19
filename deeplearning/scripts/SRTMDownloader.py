import requests
import os

for i in range(21, 72):
    for j in range(1, 24):
        if os.path.isfile("../downloaded/srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2))):
            print("[Found] srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2)))
        else:
            response = requests.get("http://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2)))
            if response.status_code == 200:
                file_name = "srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2))
                file_path = "../downloaded/" + file_name
                with open(file_path, 'wb') as f:
                    print("[Downloaded]: " + file_name)
                    f.write(response.content)
            else:
                print("[Not Found] srtm_{}_{}.zip".format(str(i).zfill(2), str(j).zfill(2)))