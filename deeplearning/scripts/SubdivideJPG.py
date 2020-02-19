from PIL import Image
import os


def split(file, chopsize, basename):
    img = Image.open(file)
    width, height = img.size
    for x0 in range(0, width, chopsize):
        for y0 in range(0, height, chopsize):
            box = (x0, y0,
                   x0 + chopsize if x0 + chopsize < width else width - 1,
                   y0 + chopsize if y0 + chopsize < height else height - 1)
            print('%s %s' % (file, box))
            img.crop(box).convert('RGB').resize((600, 600), Image.ANTIALIAS).save('../downloaded/subdivided/%s_%03d_%03d.jpg' % (basename, x0, y0))


if __name__ == "__main__":
    for file in os.listdir('../downloaded/tif'):
        basename = os.path.basename(file).replace('.tif', '')
        if file.endswith(".tif"):
            split(os.path.join('../downloaded/tif/', file), 600, basename)
