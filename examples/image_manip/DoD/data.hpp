#pragma once

#include <tuple>
#include <vector>
#include <utility>
#include <memory>

namespace data
{
    class colour_data
    {
    public:
        using colour_intensity_t = unsigned int;
        using pixel_colour_t = std::tuple<colour_intensity_t,
                                          colour_intensity_t,
                                          colour_intensity_t>;
        colour_data() : data_{nullptr}, free_pixel_index{}
        {
        }

        void set_size(std::size_t size)
        {
            data_ = std::make_unique<pixel_colour_t[]>(size);
            free_pixel_index = 0;
        }

        void insert(colour_intensity_t &r, colour_intensity_t &g, colour_intensity_t &b)
        {
            data_[free_pixel_index] = pixel_colour_t{r, g, b};
            ++free_pixel_index;
        }

        pixel_colour_t* get_nown_ptr()
        {
            return data_.get();
        }

    private:
        std::unique_ptr<pixel_colour_t[]> data_;
        std::size_t free_pixel_index;
    };

    struct position_data
    {
        using position = unsigned int;
        using pixel_position = std::pair<position, position>;
        std::vector<pixel_position> data_;
    };
} // namespace data
