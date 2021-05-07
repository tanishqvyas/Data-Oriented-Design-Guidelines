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
        virtual void set_span(std::span<pixel_colour_t>) = 0;
        virtual void apply() = 0;
        virtual ~filter();

    protected:
        std::span<pixel_colour_t> image_;
    };

    class grey_scale : public filter
    {
    public:
        grey_scale();
        virtual void set_span(std::span<pixel_colour_t>) override;
        virtual void apply() override;

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
        virtual void set_span(std::span<pixel_colour_t>) override;
        virtual void apply() override;

    private:
        const double sepia_effect_matrix[3][3] = {{0.393, 0.769, 0.189},
                                                  {0.349, 0.686, 0.168},
                                                  {0.272, 0.534, 0.131}};
    };

    class channel_adjustment : public filter
    {
    public:
        channel_adjustment(int[3]);
        virtual void set_span(std::span<pixel_colour_t>) override;
        virtual void apply() override;

    private:
        int intensity_[3];
    };

    class negative : public filter
    {
    public:
        negative();
        virtual void set_span(std::span<pixel_colour_t>) override;
        virtual void apply() override;

    private:
        const int negative_effect_matrix[4][4] = {{-1, 0, 0, 255},
                                                  {0, -1, 0, 255},
                                                  {0, 0, -1, 255},
                                                  {0, 0, 0, 1}};
    };

    class contrast : public filter
    {
    public:
        contrast(int);
        virtual void set_span(std::span<pixel_colour_t>) override;
        virtual void apply() override;

    private:
        double f_value_;
        const double contrast_effect_matrix_[4][4];
        const int v_1_matrix[3] = {-128, -128, -128};
    };

    class gamma_correction : public filter
    {
    public:
        gamma_correction(int);
        virtual void set_span(std::span<pixel_colour_t>) override;
        virtual void apply() override;

    private:
        double f_value_;
    };
}
