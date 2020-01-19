from keras.models import Sequential
from keras.layers import Conv2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense
from keras.layers import Dropout
from keras.layers import Activation
import os
import numpy as np

# Evite les messages de dépassement mémoire
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

# PART 1: LOAD DATA
train_dir = 'data/training/'
validation_dir = 'data/validation/'
test_dir = 'data/test/'

classifier = Sequential()
classifier.add(Conv2D(32, (3, 3), input_shape=(600, 600, 3), activation='relu'))
classifier.add(MaxPooling2D(pool_size=(2, 2)))
classifier.add(Conv2D(32, (3, 3), activation='relu'))
classifier.add(MaxPooling2D(pool_size=(2, 2)))
classifier.add(Conv2D(64, (3, 3), activation='relu'))
classifier.add(MaxPooling2D(pool_size=(2, 2)))
classifier.add(Flatten())
classifier.add(Dense(units=64, activation='relu'))
classifier.add(Dropout(0.5))

# output layer
classifier.add(Dense(1))
classifier.add(Activation('sigmoid'))

classifier.compile(optimizer='sgd', loss='binary_crossentropy', metrics=['accuracy'])

from keras.preprocessing.image import ImageDataGenerator

train_datagen = ImageDataGenerator(rescale=1. / 255,
                                   shear_range=0.2,
                                   zoom_range=0.2,
                                   horizontal_flip=True)

test_datagen = ImageDataGenerator(rescale=1. / 255)

training_set = train_datagen.flow_from_directory(train_dir,
                                                 target_size=(600, 600),
                                                 batch_size=32,
                                                 class_mode='binary',
                                                 shuffle=True)

test_set = test_datagen.flow_from_directory(validation_dir,
                                            target_size=(600, 600),
                                            batch_size=32,
                                            class_mode='binary',
                                            shuffle=True)

history = classifier.fit_generator(training_set,
                                   steps_per_epoch=30,
                                   epochs=2,
                                   validation_data=test_set,
                                   validation_steps=50)

from keras.preprocessing import image

print("--------------------- TERRAINS ---------------------")
for file in os.listdir('data/test/terrains/'):
    test_image = image.load_img(os.path.join('data/test/terrains/', file))
    test_image = image.img_to_array(test_image)
    test_image = np.expand_dims(test_image, axis=0)
    result = classifier.predict(test_image)
    training_indices = training_set.class_indices
    print("Probabilité d'être un terrain: " + str(result[0][0]) + " (" + file + ")")

print("--------------------- NOT A TERRAIN ---------------------")
for file in os.listdir('data/test/not_terrains/'):
    test_image = image.load_img(os.path.join('data/test/not_terrains/', file))
    test_image = image.img_to_array(test_image)
    test_image = np.expand_dims(test_image, axis=0)
    result = classifier.predict(test_image)
    training_indices = training_set.class_indices
    print("Probabilité d'être un terrain: " + str(result[0][0]) + " (" + file + ")")