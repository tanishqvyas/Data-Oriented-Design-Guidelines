#include "render_buffer.hpp"

render_buffer::render_buffer(std::vector<image> &vec_images) : colour_buffer_{},
                                                               filter_buffer_{}
{
    std::size_t colour_buffer_size = 0;
    for (auto &image_ : vec_images)
    {
        colour_buffer_size += image_.height_ * image_.width_;
    }
    colour_buffer_.set_size(colour_buffer_size);

    data::colour_data::pixel_colour_t *nown_ptr = colour_buffer_.get_nown_ptr();
    for (auto &image_ : vec_images)
    {
        nown_ptr = image_.write_colours_to_buffer(nown_ptr);
        image_.write_filters_to_buffer(filter_buffer_);
    }
}

void render_buffer::render()
{
    for (auto &filter : filter_buffer_)
    {
        std::visit(
            [](auto &f) {
                // using T = std::decay_t<decltype(f)>;
                // if constexpr (!std::is_same_v<T, std::monostate>)
                f.apply();
            },
            filter);
    }
}