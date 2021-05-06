#pragma once

#include <vector>

#include "data.hpp"
#include "filters.hpp"
#include "image.hpp"

class render_buffer
{
public:
    render_buffer(std::vector<image> &);
    void render();

private:
    data::colour_data colour_buffer;
    std::vector<filters::filter_types> filter_buffer;
};