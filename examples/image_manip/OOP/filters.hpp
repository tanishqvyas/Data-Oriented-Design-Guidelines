#pragma once

#include <vector>
#include <span>
#include <tuple>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <variant>

#include "pixel_data.hpp"

namespace filters
{
    class filter
    {
    public:
        filter();
        virtual void apply(std::vector<pixel_colour_t> &) = 0;
        virtual ~filter();
    };

    class grey_scale : public filter
    {
    public:
        grey_scale();
        grey_scale(const grey_scale &);
        grey_scale &operator=(const grey_scale &);
        virtual void apply(std::vector<pixel_colour_t> &) override;

    private:
        const double val_ = 1.0 / 3.0;
        const double grey_scale_matrix[3][3] = {{val_, val_, val_},
                                                {val_, val_, val_},
                                                {val_, val_, val_}};
    };

    class sepia : public filter
    {
    public:
        sepia();
        sepia(const sepia &);
        sepia &operator=(const sepia &);
        virtual void apply(std::vector<pixel_colour_t> &) override;

    private:
        const double sepia_effect_matrix[3][3] = {{0.393, 0.769, 0.189},
                                                  {0.349, 0.686, 0.168},
                                                  {0.272, 0.534, 0.131}};
    };

    class channel_adjustment : public filter
    {
    public:
        channel_adjustment(int[3] = {});
        channel_adjustment(const channel_adjustment &);
        channel_adjustment &operator=(const channel_adjustment &);
        virtual void apply(std::vector<pixel_colour_t> &) override;

    private:
        int intensity_[3];
    };

    class negative : public filter
    {
    public:
        negative();
        negative(const negative &);
        negative &operator=(const negative &);
        virtual void apply(std::vector<pixel_colour_t> &) override;

    private:
        const int negative_effect_matrix[4][4] = {{-1, 0, 0, 255},
                                                  {0, -1, 0, 255},
                                                  {0, 0, -1, 255},
                                                  {0, 0, 0, 1}};
    };

    class contrast : public filter
    {
    public:
        contrast(int = 0);
        contrast(const contrast &);
        contrast &operator=(const contrast &);
        virtual void apply(std::vector<pixel_colour_t> &) override;

    private:
        double f_value_;
        double contrast_effect_matrix_[4][4];
        const int v_1_matrix[3] = {-128, -128, -128};
    };

    class gamma_correction : public filter
    {
    public:
        gamma_correction(double = 1.0);
        gamma_correction(const gamma_correction &);
        gamma_correction &operator=(const gamma_correction &);
        virtual void apply(std::vector<pixel_colour_t> &) override;

    private:
        double f_value_;
    };
}
