#pragma once

#include <tuple>
#include <array>
#include <utility>
#include <memory>

namespace data
{
    using colour_intensity_t = unsigned int;
    using pixel_colour_t = std::tuple<colour_intensity_t,
                                      colour_intensity_t,
                                      colour_intensity_t>;
    template <std::size_t pixel_colour_buffer_size>
    class colour_data
    {
    public:
        colour_data() : data_{}, free_pixel_index{}
        {
        }

        void insert(colour_intensity_t &r, colour_intensity_t &g, colour_intensity_t &b)
        {
            data_[free_pixel_index] = pixel_colour_t{r, g, b};
            ++free_pixel_index;
        }

        pixel_colour_t *get_nown_ptr()
        {
            return data_.data();
        }

    private:
        std::array<pixel_colour_t, pixel_colour_buffer_size> data_;
        //std::unique_ptr<pixel_colour_t[]> data_;
        std::size_t free_pixel_index;
    };
} // namespace data
