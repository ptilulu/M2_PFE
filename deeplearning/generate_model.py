from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
from keras.preprocessing.image import ImageDataGenerator
from argparse import ArgumentParser

import os
import matplotlib.pyplot as plt

# Evite les messages de dépassement mémoire
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

# VARS
BATCH_SIZE = 128
EPOCHS = 15
IMG_HEIGHT = 600
IMG_WIDTH = 600

# GET ARGS
parser = ArgumentParser()
parser.add_argument("-e", "--epochs", dest="EPOCHS", help="Specify the number of epochs", type=int)
parser.add_argument("-b", "--batch", dest="BATCH_SIZE", help="Specify the batch size", type=int)
args = parser.parse_args()
if args.EPOCHS:
    EPOCHS = args.EPOCHS
if args.BATCH_SIZE:
    BATCH_SIZE = args.BATCH_SIZE

print("EPOCHS = %d" % EPOCHS)
print("BATCH_SIZE = %d" % BATCH_SIZE)

# PART 1: LOAD DATA
train_image_generator = ImageDataGenerator(
    rescale=1. / 255,
    rotation_range=45,
    width_shift_range=.15,
    height_shift_range=.15,
    horizontal_flip=True,
    zoom_range=0.5
)

validation_image_generator = ImageDataGenerator(
    rescale=1. / 255
)

train_data_gen = train_image_generator.flow_from_directory(
    directory='data/training/',
    target_size=(IMG_HEIGHT, IMG_WIDTH),
    batch_size=BATCH_SIZE,
    class_mode='binary',
    shuffle=True
)

val_data_gen = validation_image_generator.flow_from_directory(
    directory='data/validation/',
    target_size=(600, 600),
    batch_size=BATCH_SIZE,
    class_mode='binary',
    shuffle=True
)

# PART 2: CREATE MODEL
model = Sequential([
    Conv2D(16, 3, padding='same', activation='relu', input_shape=(IMG_HEIGHT, IMG_WIDTH, 3)),
    MaxPooling2D(),
    Conv2D(32, 3, padding='same', activation='relu'),
    MaxPooling2D(),
    Conv2D(64, 3, padding='same', activation='relu'),
    MaxPooling2D(),
    Flatten(),
    Dense(512, activation='relu'),
    Dense(1, activation='sigmoid')
])

# Compile the model
model.compile(
    optimizer='adam',
    loss='binary_crossentropy',
    metrics=['accuracy']
)

# View layers from the model
model.summary()

# Train the model
history = model.fit_generator(
    train_data_gen,
    steps_per_epoch=BATCH_SIZE,
    epochs=EPOCHS,
    validation_data=val_data_gen,
    validation_steps=BATCH_SIZE
)

# Retrieve results from training
acc = history.history['accuracy']
val_acc = history.history['val_accuracy']

loss = history.history['loss']
val_loss = history.history['val_loss']

epochs_range = range(EPOCHS)
filename = "models/MODEL_E" + str(EPOCHS) + "_B" + str(BATCH_SIZE)

plt.figure(figsize=(8, 8))
plt.subplot(1, 2, 1)
plt.plot(epochs_range, acc, label='Training Accuracy')
plt.plot(epochs_range, val_acc, label='Validation Accuracy')
plt.legend(loc='lower right')
plt.title('Training and Validation Accuracy')

plt.subplot(1, 2, 2)
plt.plot(epochs_range, loss, label='Training Loss')
plt.plot(epochs_range, val_loss, label='Validation Loss')
plt.legend(loc='upper right')
plt.title('Training and Validation Loss')
plt.savefig(filename + ".png")
plt.show()

model.save(filename + ".h5")
print("Modèle sauvegardé: " + filename)
