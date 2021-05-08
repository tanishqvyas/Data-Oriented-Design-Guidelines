# Data Oriented Design Guidelines
This repository contains the illustrated exaples for a set of actionable rules that are meant to be employed in order to enhance the code's cache friendliness, by reducing the number of L1/L2 cache misses, improving  the CPU utilization and reducing the overall runtime for a program.

# Prerequisite

**Operating System:** Ubuntu 20.04 LTS

Please make sure that you have `gcc 10.2.0`. In case you do not then install the same by running the following command:
```bash
$ sudo apt-get install gcc-10 g++-10
```

To install Valgrind and its tools, use the command:
```bash
$ sudo apt-get install valgrind
```

Also please make sure you have `Python 3.8` installed on your system. Also you need to install the `opencv` and `numpy` library. In order to install that run the following command:

```bash
$ pip3 install opencv-python numpy
```

---

# Benchmarking
## Using Cachegrind to Measure the cache misses:

Use the command:
```bash
$ valgrind --tool=cachegrind ./main.out
```

## Using Memcheck to Measure the cache misses:

Use the command:
```bash
$ valgrind --tool=memcheck --leak-check=full -s <executable_file>
```

## Measuing the Time Taken by a Program using Time:

Use the command:
```bash
$ time <executable_file>
```
**Note:**
  - Some executables already have benchmarking built in. For those examples using the `time` command is unnecessary.
  - For more information about the `time` command refer to the manual using `man time`

---

# How to run Each of the Project Folders
## 1. Vector Vs List  
  
  * Go to the folder `vector_vs_list`
  * Enable the section of code to run in the file `p1.cpp`, i.e. either vector or list code
    * Vector is a DoD technique and list is not a DoD technique
  * Run `make`
  * Run `./a.out <size_of_container>`

## 2. Collection for States
  
  * Go to the folder `Collection for States`
  * Run `make`
  * In order to run the OOP based approach run `./p1.out <number_of_agents>`
  * In order to run the DoD based approach run `./p2.out <number_of_agents>`
## 3. Image Manipulation
  
  * Go to the folder `image_manip`
  * Go to the folder `DoD`
    * Run `make`
    * Run `./main.out`
  * Go to the folder `OOP`
    * Run `make`
    * Run `./main.out`
  * Go to the folder `image_manip/Img`
    * Run `python3 dod_show_combined_rgb.py`
    * Run `python3 oop_show_combined_rgb.py`
  * Go to the folder `image_manip/Img/final_img_dod`
    * The output files will we labelled from `img_0.jpeg` to `img_9.jpeg`
  * Go to the folder `image_manip/Img/final_img_oop`
    * The output files will we labelled from `img_0.jpeg` to `img_9.jpeg`

    **Note:**
    1. To change the manipulated image and applied filters:
        1. Rename the file to convert to `base_image1.jpeg`
            1. You can choose test images from the folder `image_manip/Img/images_repository`
        2. Place the file in the folder `image_manip/Img`
        3. Run `python3 ExtractCombinedRGB.py`
        4. Copy the file `rgb_csv.csv` to the folder `image_manip/DoD/original_images`
            1. Rename the file to `img_<number_x>.csv`
            2. `<number_x>` is between **0-9**
        5. Got to the file `image_manip/DoD/main.cpp`
            1. Modify the filters applied for the `image_vec[<number_x>]` object on line **34**
        6. Run `make`
        7. Run `./main.out`
            * Go to the folder `image_manip/Img`
            * Run `python3 dod_show_combined_rgb.py`
            * Go to the folder `image_manip/Img/final_img_dod`
            * The output files will we labelled as `img_<number_x>.jpeg`

## 4. Structure of Arrays Vs Array of Structures
  
  * Go to the folder `SoA_vs_AoS`
  * Enable the section of code to run in the file `p1.cpp`, i.e. either the Structure of Arrays or Array of Structures
    * SoA is the DoD approach and AoS is the OOP approach
  * Run `make`
  * Run `./a.out <number_of_object> <number_of_iterations_over_container>`

## 5. Boolean Boon Or Bane

  * Go to `Boolean_Boon_Or_Bane` folder
  * Run `make`
  * In order to run the OOP based approach run `./p1.out`
  * In order to run the DoD based approach run `./p2.out`

---