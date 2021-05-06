#include <vector>
#include <span>
#include <tuple>

#include "data.hpp"

class grey_scale
{
public:
    grey_scale(unsigned int height, unsigned int width,
               std::span<data::colour_data::pixel_color_t> image) : height_{height}, width_{width},
                                                                    image_{image}
    {
    }

    void apply()
    {
        for (auto &pixel_colour : image_)
        {
            for (int i = 0; i < 3; ++i)
                std::get<i>(pixel_colour) = std::get<0>(pixel_colour) * grey_scale_matrix[i][0] +
                                            std::get<1>(pixel_colour) * grey_scale_matrix[i][1] +
                                            std::get<2>(pixel_colour) * grey_scale_matrix[i][2];
        }
    };

private:
    const unsigned int height_, width_;
    std::span<data::colour_data::pixel_color_t> image_;

    const double val_ = 1 / 3;
    const double grey_scale_matrix[3][3] = {{val_, val_, val_},
                                            {val_, val_, val_},
                                            {val_, val_, val_}};
};

class sepia_effect
{
public:
    sepia_effect(unsigned int height, unsigned int width,
                 std::span<data::colour_data::pixel_color_t> image) : height_{height}, width_{width},
                                                                      image_{image}
    {
    }

    void apply()
    {
        for (auto &pixel_colour : image_)
        {
            for (int i = 0; i < 3; ++i)
                std::get<i>(pixel_colour) = std::get<0>(pixel_colour) * sepia_effect_matrix[i][0] +
                                            std::get<1>(pixel_colour) * sepia_effect_matrix[i][1] +
                                            std::get<2>(pixel_colour) * sepia_effect_matrix[i][2];
        }
    };

private:
    const unsigned int height_, width_;
    std::span<data::colour_data::pixel_color_t> image_;

    const double sepia_effect_matrix[3][3] = {{0.393, 0.769, 0.189},
                                              {0.349, 0.686, 0.168},
                                              {0.272, 0.534, 0.131}};
};
