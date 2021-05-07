#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <memory>

// #include "render_buffer.hpp"
#include "data.hpp"
#include "filters.hpp"

class render_buffer;
class image
{
public:
    image(const std::string &);
    image(const image &);
    image &add_filter(filters::filter_types);
    void write_back(const std::string &);
    ~image();

private:
    std::shared_ptr<std::fstream> image_file_;
    unsigned int height_;
    unsigned int width_;
    std::vector<filters::filter_types> filter_vec_;
    std::span<data::colour_data::pixel_colour_t> image_span_;
    char load[1024]{};

    friend render_buffer;
    data::colour_data::pixel_colour_t *write_colours_to_buffer(data::colour_data::pixel_colour_t *);
    void write_filters_to_buffer(std::vector<filters::filter_types> &);
};
