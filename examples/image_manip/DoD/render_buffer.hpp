#pragma once

#include <vector>

#include "data.hpp"
#include "filters.hpp"
#include "image.hpp"

template <std::size_t pixel_colour_buffer_size = 64 * 64 * 10,
          std::size_t filter_buffer_size = 50>
class render_buffer
{
public:
    render_buffer(std::vector<image> &);
    void render();

private:
    data::colour_data<pixel_colour_buffer_size> colour_buffer_;
    std::array<filters::filter_types, filter_buffer_size> filter_buffer_;
    std::size_t filter_count_;
    // std::vector<filters::filter_types> filter_buffer_;
};

template <std::size_t pixel_colour_buffer_size,
          std::size_t filter_buffer_size>
render_buffer<pixel_colour_buffer_size, filter_buffer_size>::
    render_buffer(std::vector<image> &vec_images) : colour_buffer_{},
                                                    filter_buffer_{},
                                                    filter_count_{}
{
    for (auto &image_ : vec_images)
    {
        filter_count_ += image_.filter_vec_.size();
    }

    data::pixel_colour_t *nown_ptr = colour_buffer_.get_nown_ptr();
    std::size_t free_ind = 0;
    for (auto &image_ : vec_images)
    {
        nown_ptr = image_.write_colours_to_buffer(nown_ptr);
        free_ind = image_.write_filters_to_buffer(filter_buffer_, free_ind);
        // std::cout << free_ind << std::endl;
    }
}

template <std::size_t pixel_colour_buffer_size,
          std::size_t filter_buffer_size>
void render_buffer<pixel_colour_buffer_size, filter_buffer_size>::render()
{
    for (std::size_t i = 0; i < filter_count_; ++i)
    {
        // std::cout << "1" << std::endl;
        std::visit(
            [](auto &f) {
                // using T = std::decay_t<decltype(f)>;
                // if constexpr (!std::is_same_v<T, std::monostate>)
                f.apply();
            },
            filter_buffer_[i]);
        ++i;
    }
}
