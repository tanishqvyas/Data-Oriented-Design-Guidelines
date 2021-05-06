#include <iostream>

#include "image.hpp"

image::image(const std::string &file_name) : image_file_{new std::fstream()},
                                             height_{},
                                             width_{},
                                             filter_{},
                                             image_span_{}
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
                                 width_{obj.width_},
                                 filter_{obj.filter_},
                                 image_span_{obj.image_span_}
{
}

data::colour_data::pixel_colour_t *image::write_colours_to_buffer(data::colour_data::pixel_colour_t *nown_ptr)
{
    std::string line;
    std::string pixel;
    unsigned int pixel_value;
    unsigned int red_value;
    unsigned int green_value;
    unsigned int blue_value;

    image_span_ = std::span<data::colour_data::pixel_colour_t>{nown_ptr, height_ * width_};
    while (std::getline(*image_file_, line))
    {
        std::stringstream ss(line);
        while (std::getline(ss, pixel, ','))
        {
            std::stringstream(pixel) >> pixel_value;

            red_value = pixel_value / 65536;
            green_value = (pixel_value % 65536) / 256;
            blue_value = pixel_value % 256;
            // std::cout << pixel << std::endl;
            for (auto &pixel : image_span_)
            {
                std::get<0>(pixel) = red_value;
                std::get<1>(pixel) = green_value;
                std::get<2>(pixel) = blue_value;
            }
        }
    }
    return nown_ptr + height_ * width_;
}

void image::write_filters_to_buffer(std::vector<filters::filter_types> &filter_buffer)
{
    for (auto &filter : filter_)
    {
        filter_buffer.push_back(filter);
    }
}

image::~image()
{
}