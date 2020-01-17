from keras.models import Sequential
from keras.layers import Conv2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense
from keras.layers import Dropout
from keras.layers import Activation

classifier = Sequential()

classifier.add(Conv2D(32, (3, 3), input_shape= (600, 600, 3), activation= 'relu'))
classifier.add(MaxPooling2D(pool_size= (2, 2)))

classifier.add(Conv2D(32, (3, 3), activation= 'relu'))
classifier.add(MaxPooling2D(pool_size= (2, 2)))

classifier.add(Conv2D(64, (3, 3), activation= 'relu'))
classifier.add(MaxPooling2D(pool_size= (2, 2)))

classifier.add(Flatten())

classifier.add(Dense(units = 64, activation = 'relu'))

classifier.add(Dropout(0.5))

# output layer
classifier.add(Dense(1))
classifier.add(Activation('sigmoid'))

classifier.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])

from keras.preprocessing.image import ImageDataGenerator

train_datagen = ImageDataGenerator(rescale = 1./255,
                                   shear_range = 0.2,
                                   zoom_range = 0.2,
                                   horizontal_flip = True)

test_datagen = ImageDataGenerator(rescale = 1./255)

training_set = train_datagen.flow_from_directory('data/training/',
                                                 target_size = (200, 200),
                                                 batch_size = 32,
                                                 class_mode = 'binary')

test_set = test_datagen.flow_from_directory('data/validation/',
                                            target_size = (200, 200),
                                            batch_size = 32,
                                            class_mode = 'binary')

history = classifier.fit_generator(training_set,
                                   steps_per_epoch = 5,
                                   epochs = 1,
                                   validation_data = test_set,
                                   validation_steps = 10)

from keras.preprocessing import image
import numpy as np

test_image = image.load_img('srtm_26_17_5.tif')
result = classifier.predict(test_image)
training_set.class_indices
if result[0][0] == 1:
    prediction = 'This is a terrain'
else:
    prediction = 'This is not a terrain'

print(prediction)

test_image = image.load_img('car.jpg')
result = classifier.predict(test_image)
training_set.class_indices
if result[0][0] == 1:
    prediction = 'This is a terrain'
else:
    prediction = 'This is not a terrain'

print(prediction)