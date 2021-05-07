#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <tuple>

// #include "render_buffer.hpp"
#include "filters.hpp"
#include "pixel_data.hpp"

class render_buffer;
class image
{
public:
    image(const std::string &);
    image(const image &);
    image &add_filter(filters::filter *);
    void write_back(const std::string &);
    void render();
    ~image();

private:
    std::shared_ptr<std::fstream> image_file_;
    unsigned int height_;
    unsigned int width_;
    std::vector<filters::filter *> filter_vec_;
    std::vector<pixel_colour_t> image_vec_;
};
