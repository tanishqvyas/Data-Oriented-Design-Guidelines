import os
import cv2
import numpy as np
import csv
from PIL import Image

IMAGE_PATH = os.path.join("..", "OOP", "modified_images")
DES_IMG_PATH = os.path.join(".", "final_img_oop")
TOTAL_NUMBER_OF_IMGS = 10


for i in range(TOTAL_NUMBER_OF_IMGS):
    all_rgb = []
    with open(os.path.join(IMAGE_PATH, "img_" + str(i) + ".csv")) as csv_file:
        csv_reader = csv.reader(csv_file)
        next(csv_reader)  # Ignore the first line
        for row in csv_reader:
            row_rgb = []
            for rgb_combined in row:
                red = int(rgb_combined) // 65536
                green = (int(rgb_combined) % 65536) // 256
                blue = int(rgb_combined) % 256

                row_rgb.append([blue, green, red])  # opencv uses BGR

            all_rgb.append(row_rgb)

    cv2.imwrite(os.path.join(DES_IMG_PATH, "img_" + str(i) + ".jpeg"), np.array(all_rgb))
