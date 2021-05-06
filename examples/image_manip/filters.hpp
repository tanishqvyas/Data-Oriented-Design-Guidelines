#pragma once

#include <vector>
#include <span>
#include <tuple>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <variant>

#include "data.hpp"

namespace filters
{
    class grey_scale
    {
    public:
        grey_scale(std::span<data::colour_data::pixel_colour_t>);

        void apply();

    private:
        std::span<data::colour_data::pixel_colour_t> image_;

        const double val_ = 1 / 3;
        const double grey_scale_matrix[3][3] = {{val_, val_, val_},
                                                {val_, val_, val_},
                                                {val_, val_, val_}};
    };

    class sepia
    {
    public:
        sepia(std::span<data::colour_data::pixel_colour_t>);

        void apply();

    private:
        std::span<data::colour_data::pixel_colour_t> image_;

        const double sepia_effect_matrix[3][3] = {{0.393, 0.769, 0.189},
                                                  {0.349, 0.686, 0.168},
                                                  {0.272, 0.534, 0.131}};
    };

    class channel_adjustment
    {
    public:
        channel_adjustment(int[3], std::span<data::colour_data::pixel_colour_t>);

        void apply();

    private:
        std::span<data::colour_data::pixel_colour_t> image_;
        int intensity_[3];
    };

    class negative
    {
    public:
        negative(std::span<data::colour_data::pixel_colour_t>);

        void apply();

    private:
        std::span<data::colour_data::pixel_colour_t> image_;
        const int negative_effect_matrix[4][4] = {{-1, 0, 0, 255},
                                                  {0, -1, 0, 255},
                                                  {0, 0, -1, 255},
                                                  {0, 0, 0, 1}};
    };

    class contrast
    {
    public:
        contrast(std::span<data::colour_data::pixel_colour_t>, int);

        void apply();

    private:
        std::span<data::colour_data::pixel_colour_t> image_;
        double f_value_;
        const double contrast_effect_matrix_[4][4];
        const int v_1_matrix[3] = {-128, -128, -128};
    };

    class gamma_correction
    {
    public:
        gamma_correction(std::span<data::colour_data::pixel_colour_t>, int);

        void apply();

    private:
        std::span<data::colour_data::pixel_colour_t> image_;
        double f_value_;
    };

    using filter_types = std::variant<grey_scale,
                                      sepia,
                                      channel_adjustment,
                                      negative,
                                      contrast,
                                      gamma_correction>;
}