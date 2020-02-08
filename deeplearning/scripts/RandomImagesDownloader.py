import requests
from argparse import ArgumentParser


# Functions
def downloadRandomImages(number):
    for i in range(number):
        url = "https://picsum.photos/600/600/?random"
        response = requests.get(url)
        if response.status_code == 200:
            file_name = 'others_{}.jpg'.format(i)
            file_path = "../data/training/others/" + file_name
            with open(file_path, 'wb') as f:
                print("Saving: " + file_name)
                f.write(response.content)


# Vars
TRAINING_IMAGES = 2000
VALIDATION_IMAGES = 650
TEST_IMAGES = 100

# GET ARGS
parser = ArgumentParser()
parser.add_argument("-t", "--training", dest="TRAINING", help="Specify the training data size", type=int)
parser.add_argument("-v", "--validation", dest="VALIDATION", help="Specify the validation data size", type=int)
parser.add_argument("-r", "--test", dest="TEST", help="Specify the test data size", type=int)
args = parser.parse_args()
if args.TRAINING:
    TRAINING_IMAGES = args.TRAINING
if args.VALIDATION:
    VALIDATION_IMAGES = args.VALIDATION
if args.TEST:
    TEST_IMAGES = args.TEST

print("--------------- TRAINING ---------------")
downloadRandomImages(TRAINING_IMAGES)
print("--------------- VALIDATION ---------------")
downloadRandomImages(VALIDATION_IMAGES)
print("--------------- TEST ---------------")
downloadRandomImages(TEST_IMAGES)
