#include <tuple>
#include <vector>
#include <utility>


namespace data
{
    struct colour_data {
        using colour_intensity_t = unsigned int;
        using pixel_color_t = std::tuple<colour_intensity_t,
                                         colour_intensity_t,
                                         colour_intensity_t>;
        std::vector<pixel_color_t> data_;
    };

    struct position_data {
        using position = unsigned int;
        using pixel_position = std::pair<position, position>;
        std::vector<pixel_position> data;
    };
} // namespace data
