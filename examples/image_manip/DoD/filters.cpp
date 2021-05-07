#include "filters.hpp"
#include <iostream>

filters::grey_scale::grey_scale() : image_{}
{
}

filters::grey_scale::grey_scale(const grey_scale &obj) : image_{obj.image_}
{
}

filters::grey_scale &filters::grey_scale::operator=(const grey_scale &obj)
{
    image_ = obj.image_;
    return *this;
}

void filters::grey_scale::set_span(std::span<data::pixel_colour_t> image)
{
    image_ = image;
}

void filters::grey_scale::apply()
{
    for (auto &pixel_colour : image_)
    {
        // std::cout << std::get<0>(pixel_colour) * 0.5 << std::endl;
        // std::cout << std::get<0>(pixel_colour) * grey_scale_matrix[0][0] +
        //                  std::get<1>(pixel_colour) * grey_scale_matrix[0][1] +
        //                  std::get<2>(pixel_colour) * grey_scale_matrix[0][2]
        //           << std::endl;
        std::get<0>(pixel_colour) = static_cast<unsigned int>(std::get<0>(pixel_colour) * grey_scale_matrix[0][0] +
                                                              std::get<1>(pixel_colour) * grey_scale_matrix[0][1] +
                                                              std::get<2>(pixel_colour) * grey_scale_matrix[0][2]);
        std::get<1>(pixel_colour) = static_cast<unsigned int>(std::get<0>(pixel_colour) * grey_scale_matrix[1][0] +
                                                              std::get<1>(pixel_colour) * grey_scale_matrix[1][1] +
                                                              std::get<2>(pixel_colour) * grey_scale_matrix[1][2]);
        std::get<2>(pixel_colour) = static_cast<unsigned int>(std::get<0>(pixel_colour) * grey_scale_matrix[2][0] +
                                                              std::get<1>(pixel_colour) * grey_scale_matrix[2][1] +
                                                              std::get<2>(pixel_colour) * grey_scale_matrix[2][2]);
    }
}

filters::sepia::sepia() : image_{}
{
}

filters::sepia::sepia(const filters::sepia &obj) : image_{obj.image_}
{
}

filters::sepia &filters::sepia::operator=(const filters::sepia &obj)
{
    image_ = obj.image_;
    return *this;
}

void filters::sepia::set_span(std::span<data::pixel_colour_t> image)
{
    image_ = image;
}

void filters::sepia::apply()
{
    for (auto &pixel_colour : image_)
    {
        std::get<0>(pixel_colour) = static_cast<unsigned int>(std::get<0>(pixel_colour) * sepia_effect_matrix[0][0] +
                                                              std::get<1>(pixel_colour) * sepia_effect_matrix[0][1] +
                                                              std::get<2>(pixel_colour) * sepia_effect_matrix[0][2]);
        std::get<1>(pixel_colour) = static_cast<unsigned int>(std::get<0>(pixel_colour) * sepia_effect_matrix[1][0] +
                                                              std::get<1>(pixel_colour) * sepia_effect_matrix[1][1] +
                                                              std::get<2>(pixel_colour) * sepia_effect_matrix[1][2]);
        std::get<2>(pixel_colour) = static_cast<unsigned int>(std::get<0>(pixel_colour) * sepia_effect_matrix[2][0] +
                                                              std::get<1>(pixel_colour) * sepia_effect_matrix[2][1] +
                                                              std::get<2>(pixel_colour) * sepia_effect_matrix[2][2]);
    }
}

filters::channel_adjustment::channel_adjustment() : image_{},
                                                    intensity_{0,
                                                               0,
                                                               0}
{
}

filters::channel_adjustment::channel_adjustment(int intensity[3]) : image_{},
                                                                    intensity_{intensity[0],
                                                                               intensity[1],
                                                                               intensity[2]}
{
    assert((intensity[0] >= -150 && intensity[0] <= 150));
    assert((intensity[1] >= -150 && intensity[1] <= 150));
    assert((intensity[2] >= -150 && intensity[2] <= 150));
}

filters::channel_adjustment::channel_adjustment(const channel_adjustment &obj) : image_{obj.image_},
                                                                                 intensity_{obj.intensity_[0],
                                                                                            obj.intensity_[1],
                                                                                            obj.intensity_[2]}
{
}

filters::channel_adjustment &filters::channel_adjustment::operator=(const channel_adjustment &obj)
{
    image_ = obj.image_;
    intensity_[0] = obj.intensity_[0];
    intensity_[1] = obj.intensity_[1];
    intensity_[2] = obj.intensity_[2];
    return *this;
}

void filters::channel_adjustment::set_span(std::span<data::pixel_colour_t> image)
{
    image_ = image;
}

void filters::channel_adjustment::apply()
{
    const int Brightest = 255;
    const int Darkest = 0;

    for (auto &pixel_colour : image_)
    {
        const int r = std::get<0>(pixel_colour);
        const int g = std::get<1>(pixel_colour);
        const int b = std::get<2>(pixel_colour);
        // std::cout << std::clamp(r + intensity_[0], Darkest, Brightest) << std::endl;
        std::get<0>(pixel_colour) = static_cast<unsigned int>(std::clamp(r + intensity_[0], Darkest, Brightest));
        std::get<1>(pixel_colour) = static_cast<unsigned int>(std::clamp(g + intensity_[1], Darkest, Brightest));
        std::get<2>(pixel_colour) = static_cast<unsigned int>(std::clamp(b + intensity_[2], Darkest, Brightest));
    }
}

filters::negative::negative() : image_{}
{
}

filters::negative::negative(const filters::negative &obj) : image_{obj.image_}
{
}
filters::negative &filters::negative::operator=(const filters::negative &obj)
{
    image_ = obj.image_;
    return *this;
}

void filters::negative::set_span(std::span<data::pixel_colour_t> image)
{
    image_ = image;
}

void filters::negative::apply()
{
    const unsigned int Brightest = 255U;
    const unsigned int Darkest = 0U;
    for (auto &pixel_colour : image_)
    {
        const unsigned int r = std::get<0>(pixel_colour);
        const unsigned int g = std::get<1>(pixel_colour);
        const unsigned int b = std::get<2>(pixel_colour);

        const unsigned int new_r_value = r * negative_effect_matrix[0][0] +
                                         g * negative_effect_matrix[0][1] +
                                         b * negative_effect_matrix[0][2] +
                                         negative_effect_matrix[0][3];

        const unsigned int new_g_value = r * negative_effect_matrix[1][0] +
                                         g * negative_effect_matrix[1][1] +
                                         b * negative_effect_matrix[1][2] +
                                         negative_effect_matrix[1][3];

        const unsigned int new_b_value = r * negative_effect_matrix[2][0] +
                                         g * negative_effect_matrix[2][1] +
                                         b * negative_effect_matrix[2][2] +
                                         negative_effect_matrix[2][3];

        std::get<0>(pixel_colour) = std::clamp(new_r_value, Darkest, Brightest);
        std::get<1>(pixel_colour) = std::clamp(new_g_value, Darkest, Brightest);
        std::get<2>(pixel_colour) = std::clamp(new_b_value, Darkest, Brightest);
    }
}

filters::contrast::contrast(int value) : image_{},
                                         f_value_{
                                             static_cast<double>(
                                                 (259.0 * (value + 255.0)) / (255.0 * (259.0 - value)))},
                                         contrast_effect_matrix_{
                                             {f_value_, 0, 0, 128.0},
                                             {0, f_value_, 0, 128.0},
                                             {0, 0, f_value_, 128.0},
                                             {0, 0, 0, 1.0}}

{
    assert((value >= -100 && value <= 100));
}

filters::contrast::contrast(const filters::contrast &obj) : image_{obj.image_},
                                                            f_value_{obj.f_value_},
                                                            contrast_effect_matrix_{
                                                                {f_value_, 0, 0, 128.0},
                                                                {0, f_value_, 0, 128.0},
                                                                {0, 0, f_value_, 128.0},
                                                                {0, 0, 0, 1.0}}
{
}
filters::contrast &filters::contrast::operator=(const filters::contrast &obj)
{
    image_ = obj.image_;
    f_value_ = obj.f_value_;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            contrast_effect_matrix_[i][j] = obj.contrast_effect_matrix_[i][j];

    return *this;
}

void filters::contrast::set_span(std::span<data::pixel_colour_t> image)
{
    image_ = image;
}

void filters::contrast::apply()
{
    const unsigned int Brightest = 255U;
    const unsigned int Darkest = 0U;
    for (auto &pixel_colour : image_)
    {
        const unsigned int r = std::get<0>(pixel_colour);
        const unsigned int g = std::get<1>(pixel_colour);
        const unsigned int b = std::get<2>(pixel_colour);

        const unsigned int new_r_value = static_cast<unsigned int>(r * contrast_effect_matrix_[0][0] +
                                                                   g * contrast_effect_matrix_[0][1] +
                                                                   b * contrast_effect_matrix_[0][2] +
                                                                   contrast_effect_matrix_[0][3] +
                                                                   v_1_matrix[0]);

        const unsigned int new_g_value = static_cast<unsigned int>(r * contrast_effect_matrix_[1][0] +
                                                                   g * contrast_effect_matrix_[1][1] +
                                                                   b * contrast_effect_matrix_[1][2] +
                                                                   contrast_effect_matrix_[1][3] +
                                                                   v_1_matrix[0]);

        const unsigned int new_b_value = static_cast<unsigned int>(r * contrast_effect_matrix_[2][0] +
                                                                   g * contrast_effect_matrix_[2][1] +
                                                                   b * contrast_effect_matrix_[2][2] +
                                                                   contrast_effect_matrix_[2][3] +
                                                                   v_1_matrix[0]);

        std::get<0>(pixel_colour) = std::clamp(new_r_value, Darkest, Brightest);
        std::get<1>(pixel_colour) = std::clamp(new_g_value, Darkest, Brightest);
        std::get<2>(pixel_colour) = std::clamp(new_b_value, Darkest, Brightest);
    }
}

filters::gamma_correction::gamma_correction(double value) : image_{},
                                                            f_value_{value != 0.0 ? static_cast<double>(1.0 / value) : 0.0}
{
    assert((value > 0.0 && value <= 10.0));
    assert((f_value_ != 0.0));
}

filters::gamma_correction::gamma_correction(const gamma_correction &obj) : image_{obj.image_},
                                                                           f_value_{obj.f_value_}
{
}
filters::gamma_correction &filters::gamma_correction::operator=(const filters::gamma_correction &obj)
{
    image_ = obj.image_;
    f_value_ = obj.f_value_;
    return *this;
}

void filters::gamma_correction::set_span(std::span<data::pixel_colour_t> image)
{
    image_ = image;
}

void filters::gamma_correction::apply()
{
    const unsigned int Brightest = 255U;
    const unsigned int Darkest = 0U;
    for (auto &pixel_colour : image_)
    {
        const unsigned int r = std::get<0>(pixel_colour);
        const unsigned int g = std::get<1>(pixel_colour);
        const unsigned int b = std::get<2>(pixel_colour);

        const unsigned int new_r_value = static_cast<unsigned int>(255.0 * std::pow(r / 255.0, f_value_));
        const unsigned int new_g_value = static_cast<unsigned int>(255.0 * std::pow(g / 255.0, f_value_));
        const unsigned int new_b_value = static_cast<unsigned int>(255.0 * std::pow(b / 255.0, f_value_));

        std::get<0>(pixel_colour) = std::clamp(new_r_value, Darkest, Brightest);
        std::get<1>(pixel_colour) = std::clamp(new_g_value, Darkest, Brightest);
        std::get<2>(pixel_colour) = std::clamp(new_b_value, Darkest, Brightest);
    }
}
