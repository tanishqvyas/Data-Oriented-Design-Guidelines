import os
import cv2
import numpy as np
import csv

# New Sizes
RESIZED_HEIGHT = 64
RESIZED_WIDTH = 64

# IMAGE_PATH = os.path.join("base_image.png")
IMAGE_PATH = os.path.join("base_image1.jpeg")

# Reading in the BASE IMAGE
img = cv2.imread(IMAGE_PATH)

# images are converted to 1:1 dimensions
img = cv2.resize(img, (RESIZED_HEIGHT, RESIZED_WIDTH)).tolist()

# Opening a CSV to write the encoded image
rgb_csv = open("rgb_csv.csv", "w")
csv_writer = csv.writer(rgb_csv)

# Writing the size of the image
csv_writer.writerow([RESIZED_HEIGHT, RESIZED_WIDTH])

# Encoding all the pixels in the image
for x in range(RESIZED_HEIGHT):
    row = []
    for y in range(RESIZED_WIDTH):

        # Combining the RGB values
        rgb_combined = img[x][y][2] * 65536 + img[x][y][1] * 256 + img[x][y][0]
        row.append(rgb_combined)

    csv_writer.writerow(row)

# closing the csv file
rgb_csv.close()
