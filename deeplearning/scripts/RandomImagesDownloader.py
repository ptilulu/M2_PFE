import requests

# Training
for i in range(200):
    url = "https://picsum.photos/600/600/?random"
    response = requests.get(url)
    if response.status_code == 200:
        file_name = 'not_terrain_{}.jpg'.format(i)
        file_path = "../data/training/not_terrains/" + file_name
        with open(file_path, 'wb') as f:
            print("saving: " + file_name)
            f.write(response.content)

# Validation
for i in range(100):
    url = "https://picsum.photos/600/600/?random"
    response = requests.get(url)
    if response.status_code == 200:
        file_name = 'not_terrain_{}.jpg'.format(i)
        file_path = "../data/validation/not_terrains/" + file_name
        with open(file_path, 'wb') as f:
            print("saving: " + file_name)
            f.write(response.content)

# Test
for i in range(100):
    url = "https://picsum.photos/600/600/?random"
    response = requests.get(url)
    if response.status_code == 200:
        file_name = 'not_terrain_{}.jpg'.format(i)
        file_path = "../data/test/not_terrains/" + file_name
        with open(file_path, 'wb') as f:
            print("saving: " + file_name)
            f.write(response.content)