from keras.models import load_model
from keras.preprocessing import image

import os
import numpy as np
import sys


# FUNCTIONS
def test_images(model, path):
    for file in os.listdir(path):
        img = image.load_img(os.path.join(path, file))
        img = image.img_to_array(img)
        img = np.expand_dims(img, axis=0)
        result = model.predict(img)
        print("---------------- Fichier: " + file + " ----------------")
        print(result)


model_path = sys.argv[1]
if not os.path.exists(model_path):
    print("Erreur: veuillez spécifier un nom de modèle à charger valide!")
    exit(1)

# On charge notre modèle existant
model = load_model(model_path)

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
