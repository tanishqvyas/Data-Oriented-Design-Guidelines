#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <memory>

// #include "render_buffer.hpp"
#include "data.hpp"

class image
{
public:
    image(const std::string &);
    image(const image &);
    void write_to_buffer(const data::colour_data &);
    ~image();

private:
    std::shared_ptr<std::fstream> image_file_;
    unsigned int height_;
    unsigned int width_;
};
