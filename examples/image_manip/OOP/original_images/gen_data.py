import random


def pixel_value():
    r_ = random.randint(0, 255)
    g_ = random.randint(0, 255)
    b_ = random.randint(0, 255)
    return str(r_*65536 + g_*256 + b_)


img = "img_"

height_ = 64
width_ = 64

for i in range(10):
    file_name_ = img + str(i) + ".csv"
    with open(file_name_, "w") as fhandle:
        fhandle.write(str(height_) + "," + str(width_) + "\n")
        ele = [[pixel_value() for _ in range(width_)] for _ in range(height_)]
        for i in range(height_):
            line = ",".join(ele[i])
            line += "\n"
            fhandle.write(line)
