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

        std::vector<std::pair<position, position>> data;
    };
} // namespace data
