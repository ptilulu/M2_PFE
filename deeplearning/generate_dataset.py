import numpy as np
import matplotlib.pyplot as plt
import os
import cv2

DATADIR = "data/gan"
# CATEGORIES = ["terrains", "not_terrains"]

IMG_SIZE = 28
training_data = []


def create_training_data():
    # for category in CATEGORIES:
    #     path = os.path.join(DATADIR, category)
    #     class_num = CATEGORIES.index(category)
    for img in os.listdir(DATADIR):
        if not img.endswith(('.tif', '.jpg')):
            continue
        print(img)
        try:
            img_array = cv2.imread(os.path.join(DATADIR, img), cv2.IMREAD_GRAYSCALE)
            new_array = cv2.resize(img_array, (IMG_SIZE, IMG_SIZE))
            training_data.append([new_array])
        except Exception as e:
            pass


create_training_data()

training_data = np.array(training_data).reshape(-1, IMG_SIZE, IMG_SIZE, 1)
np.save('datasets/dcgan.npy', training_data)
