import os
import cv2
import numpy as np
import csv
from PIL import Image

# IMAGE_PATH = os.path.join("..", "DoD", "modified_images")
DES_IMG_PATH = os.path.join(".", "final_img")
TOTAL_NUMBER_OF_IMGS = 1

# os.path.join(IMAGE_PATH, "img_" + str(i) + ".csv")
for i in range(TOTAL_NUMBER_OF_IMGS):
    all_rgb = []
    with open("rgb_csv.csv") as csv_file:
        csv_reader = csv.reader(csv_file)
        next(csv_reader)  # Ignore the first line
        for row in csv_reader:
            row_rgb = []
            for rgb_combined in row:
                # rgb_combined = int(rgb_combined)
                # red = (int(rgb_combined) >> 16) & 0xFF
                # green = (int(rgb_combined) >> 8) & 0xFF
                # blue = int(rgb_combined) & 0xFF
                # print(rgb_combined)``
                red = int(rgb_combined) // 65536
                green = (int(rgb_combined) % 65536) // 256
                blue = int(rgb_combined) % 256

                row_rgb.append([blue, green, red])  # opencv uses BGR
                # row_rgb.append([red, green, blue])  # Pillow uses BGR

            all_rgb.append(row_rgb)
    # print(np.array(all_rgb).shape)
    print(all_rgb)
    cv2.imwrite(os.path.join(DES_IMG_PATH, "img_" + str(i) + ".jpeg"), np.array(all_rgb))
    # cv2.imshow("wow", np.array(all_rgb))
    # cv2.waitKey(0)
    # image = Image.fromarray(np.array(all_rgb), "RGB")
    # image.save(os.path.join(DES_IMG_PATH, "img_" + str(i) + ".png"))
    # image.show()
    # cv2.imwrite(os.path.join(DES_IMG_PATH, "img_" + str(i) + ".png"), np.array(all_rgb))
    # cv2.imshow("img_" + str(i) + ".png", np.array(all_rgb))
    # cv2.waitKey(0)
    # print("hello")
    # close(csv_file)
