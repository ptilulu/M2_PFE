from keras.models import load_model
from keras.preprocessing import image
from argparse import ArgumentParser

import os
import numpy as np


# FUNCTIONS
def test_images(model, path):
    for file in os.listdir(path):
        img = image.load_img(os.path.join(path, file))
        img = image.img_to_array(img)
        img = np.expand_dims(img, axis=0)
        result = model.predict(img)
        print("---------------- Fichier: " + file + " ----------------")
        print(result)


# GET ARGS
parser = ArgumentParser()
parser.add_argument("model", dest="model_path", help="Model file to load", metavar="FILE")
args = parser.parse_args()
if not os.path.exists(args.model_path):
    print("Erreur: veuillez spécifier un nom de modèle à charger valide!")
    exit(1)

# On charge notre modèle existant
model = load_model(args.model_path)

# On le recompile
model.compile(
    optimizer='adam',
    loss='binary_crossentropy',
    metrics=['accuracy']
)

# PART 3: TEST MODEL
print("--------------------- TERRAINS ---------------------")
test_images(model, 'data/test/terrains/')

print("--------------------- NOT A TERRAIN ---------------------")
test_images(model, 'data/test/not_terrains/')
