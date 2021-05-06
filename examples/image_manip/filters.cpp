#include "filters.hpp"

filters::grey_scale::grey_scale(std::span<data::colour_data::pixel_colour_t> image) : image_{image}
{
}

void filters::grey_scale::apply()
{
    for (auto &pixel_colour : image_)
    {
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

filters::sepia::sepia(std::span<data::colour_data::pixel_colour_t> image) : image_{image}
{
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

filters::channel_adjustment::channel_adjustment(int intensity[3],
                                                std::span<data::colour_data::pixel_colour_t> image) : image_{image},
                                                                                                      intensity_{intensity[0],
                                                                                                                 intensity[1],
                                                                                                                 intensity[2]}
{
}

void filters::channel_adjustment::apply()
{
    const unsigned int Brightest = 255U;
    const unsigned int Darkest = 0U;

    for (auto &pixel_colour : image_)
    {
        const unsigned int r = std::get<0>(pixel_colour);
        const unsigned int g = std::get<1>(pixel_colour);
        const unsigned int b = std::get<2>(pixel_colour);
        std::get<0>(pixel_colour) = std::clamp(r + intensity_[0], Darkest, Brightest);
        std::get<1>(pixel_colour) = std::clamp(g + intensity_[1], Darkest, Brightest);
        std::get<2>(pixel_colour) = std::clamp(b + intensity_[2], Darkest, Brightest);
    }
}

filters::negative::negative(std::span<data::colour_data::pixel_colour_t> image) : image_{image}
{
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

filters::contrast::contrast(std::span<data::colour_data::pixel_colour_t> image, int value) : image_{image},
                                                                                             f_value_{
                                                                                                 static_cast<double>(
                                                                                                     (259 * (value + 255)) / (255 * (259 - value)))},
                                                                                             contrast_effect_matrix_{
                                                                                                 {f_value_, 0, 0, 128},
                                                                                                 {0, f_value_, 0, 128},
                                                                                                 {0, 0, f_value_, 128},
                                                                                                 {0, 0, 0, 1}}

{
    assert((value >= -100 && value <= 100));
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

filters::gamma_correction::gamma_correction(std::span<data::colour_data::pixel_colour_t> image,
                                            int value) : image_{image},
                                                         f_value_{value != 0 ? static_cast<double>(1 / value) : 0}
{
    assert((value > 0 && value <= 10));
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

        const unsigned int new_r_value = static_cast<unsigned int>(255 * std::pow(r / 255, f_value_));
        const unsigned int new_g_value = static_cast<unsigned int>(255 * std::pow(g / 255, f_value_));
        const unsigned int new_b_value = static_cast<unsigned int>(255 * std::pow(b / 255, f_value_));

        std::get<0>(pixel_colour) = std::clamp(new_r_value, Darkest, Brightest);
        std::get<1>(pixel_colour) = std::clamp(new_g_value, Darkest, Brightest);
        std::get<2>(pixel_colour) = std::clamp(new_b_value, Darkest, Brightest);
    }
}
