import os
import cv2
import numpy as np
import csv

# Defining filepaths needed for the operations
IMAGE_PATH = os.path.join("..", "DoD", "modified_images")
DES_IMG_PATH = os.path.join(".", "final_img_dod")
TOTAL_NUMBER_OF_IMGS = 10

# Iterating over all the images
for i in range(TOTAL_NUMBER_OF_IMGS):
    all_rgb = []

    # Opening each image and decoding the processed values
    with open(os.path.join(IMAGE_PATH, "img_" + str(i) + ".csv")) as csv_file:
        csv_reader = csv.reader(csv_file)
        next(csv_reader)  # Ignore the first line

        # Decoding and saving image rows
        for row in csv_reader:
            row_rgb = []
            for rgb_combined in row:

                # Decoding Logic
                red = int(rgb_combined) // 65536
                green = (int(rgb_combined) % 65536) // 256
                blue = int(rgb_combined) % 256

                row_rgb.append([blue, green, red])  # opencv uses BGR

            all_rgb.append(row_rgb)

    # Saving the image
    cv2.imwrite(os.path.join(DES_IMG_PATH, "img_" +
                             str(i) + ".jpeg"), np.array(all_rgb))
