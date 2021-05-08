#include <iostream>
#include <fstream>

#include "image.hpp"

image::image(const std::string &file_name) : image_file_{new std::fstream()},
                                             height_{},
                                             width_{},
                                             filter_vec_{},
                                             image_vec_{}
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

    std::string str_pixel_value;
    unsigned int ui_pixel_value;
    unsigned int red_value;
    unsigned int green_value;
    unsigned int blue_value;

    // auto it_pixel = image_vec_.begin();
    while (std::getline(*image_file_, line))
    {
        std::stringstream ss(line);
        while (std::getline(ss, str_pixel_value, ','))
        {
            // assert((it_pixel != image_vec_.end()));
            std::stringstream(str_pixel_value) >> ui_pixel_value;

            red_value = ui_pixel_value / 65536;
            green_value = (ui_pixel_value % 65536) / 256;
            blue_value = ui_pixel_value % 256;

#if DEBUG
            std::cout << red_value << ",";
            std::cout << green_value << ",";
            std::cout << blue_value << ",";
#endif
            image_vec_.emplace_back(red_value, green_value, blue_value);
        }
    }
    // std::cout << "1" << std::endl;
}

image::image(const image &obj) : image_file_{obj.image_file_},
                                 height_{obj.height_},
                                 width_{obj.width_},
                                 filter_vec_{obj.filter_vec_},
                                 image_vec_{obj.image_vec_}
{
}

image &image::add_filter(filters::filter *filter)
{
    filter_vec_.push_back(filter);
    assert((filter != nullptr));
    return *this;
}

void image::render()
{
    for (auto it = filter_vec_.begin(); it != filter_vec_.end(); ++it)
    {
        // std::cout << "3" << std::endl;
        assert((*it != nullptr));
        (*it)->apply(image_vec_);
    }
}

void image::write_back(const std::string &path_to_dest)
{
    std::cout << path_to_dest << std::endl;
    unsigned int line_width_tracker = 0;
    std::fstream destination_file;
    destination_file.open(path_to_dest, std::fstream::out);
    assert((destination_file.is_open()));
    destination_file << height_ << "," << width_ << std::endl;
    for (auto &pixel : image_vec_)
    {
        ++line_width_tracker;
        //  r*65536 + g*256 + b
        unsigned int temp_ = std::get<0>(pixel) * 65536 +
                             std::get<1>(pixel) * 256 +
                             std::get<2>(pixel);
        if (line_width_tracker == width_)
        {
            destination_file << temp_ << std::endl;
            line_width_tracker = 0;
        }
        else
        {
            destination_file << temp_ << ",";
        }
    }

    destination_file.close();
}

image::~image()
{
    for (auto it = filter_vec_.begin(); it != filter_vec_.end(); ++it)
    {
        // std::cout << "3" << std::endl;
        assert((*it != nullptr));
        delete *it;
    }
}