#include <iostream>

#include "image.hpp"

image::image(const std::string &file_name) : image_file_{new std::fstream()},
                                             height_{},
                                             width_{}
{
    image_file_->open(file_name);

    std::string line;
    std::string pixel;

    std::getline(*image_file_, line);
    std::stringstream ss(line);

    std::getline(ss, pixel, ',');
    std::stringstream(pixel) >> height_;

    std::getline(ss, pixel, ',');
    std::stringstream(pixel) >> width_;

    // std::cout << height_ << width_ << std::endl;
}

image::image(const image &obj) : image_file_{obj.image_file_},
                                 height_{obj.height_},
                                 width_{obj.width_}
{
}

void image::write_to_buffer(const data::colour_data &obj)
{
    std::string line;
    std::string pixel;
    while (std::getline(*image_file_, line))
    {
        std::stringstream ss(line);
        while (std::getline(ss, pixel, ','))
        {
            std::cout << pixel << std::endl;
            // TODO: add pixel to the image colour buffer
        }
    }
}

image::~image()
{
    // image_file_.close();
}