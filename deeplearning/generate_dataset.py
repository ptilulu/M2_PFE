import cv2
import glob
import numpy as np

# Train data
train = []
train_labels = []

files = glob.glob("data/training/terrains/*.tif")  # your image path
for trainFile in files:
    image = cv2.imread(trainFile)
    train.append(image)
    train_labels.append([1., 0.])

files = glob.glob("data/training/not_terrains/*.jpg")
for trainFile in files:
    image = cv2.imread(trainFile)
    train.append(image)
    train_labels.append([0., 1.])

train = np.array(train, dtype='float32')  # as mnist
train_labels = np.array(train_labels, dtype='float64')  # as mnist
# convert (number of images x height x width x number of channels) to (number of images x (height * width *3))
# for example (120 * 40 * 40 * 3)-> (120 * 4800)
train = np.reshape(train, [train.shape[0], train.shape[1] * train.shape[2] * train.shape[3]])

# save numpy array as .npy formats
np.save('datasets/train', train)
np.save('datasets/train_labels', train_labels)

# Test data
validation = []
validation_labels = []
files = glob.glob("data/validation/terrains/*.tif")
for myFile in files:
    image = cv2.imread(myFile)
    validation.append(image)
    validation_labels.append([1., 0.])  # class1
files = glob.glob("data/validation/not_terrains/*.jpg")
for myFile in files:
    image = cv2.imread(myFile)
    validation.append(image)
    validation_labels.append([0., 1.])  # class2

validation = np.array(validation, dtype='float32')  # as mnist example
validation_labels = np.array(validation_labels, dtype='float64')  # as mnist
validation = np.reshape(validation, [validation.shape[0], validation.shape[1] * validation.shape[2] * validation.shape[3]])

# save numpy array as .npy formats
np.save('datasets/validation', validation)  # saves test.npy
np.save('datasets/validation_labels', validation_labels)

# Importing required libraries
# import os
# import numpy as np
# from PIL import Image
#
# IMAGE_SIZE = 600
# IMAGE_CHANNELS = 3
# IMAGE_DIR = "data/gan"
#
# # Defining image dir path. Change this if you have different directory
# images_path = IMAGE_DIR
#
# training_data = []
#
# for file in os.listdir(images_path):
#     if file.endswith((".tif", ".jpg")):
#         path = os.path.join(images_path, file)
#         image = Image.open(path).resize((IMAGE_SIZE, IMAGE_SIZE), Image.ANTIALIAS)
#         training_data.append(np.asarray(image))
#
# training_data = np.reshape(training_data, (-1, IMAGE_SIZE, IMAGE_SIZE, IMAGE_CHANNELS))
# training_data = training_data / 127.5 - 1
#
# print('Saving...')
# np.save('datasets/dcgan.npy', training_data)
