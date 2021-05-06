#include <iostream>
#include <string>
#include <vector>

#include "image.hpp"
#include "animations.hpp"
#include "data.hpp"

int main()
{
    const std::string Base_Image_Path{"./Img"};
    const std::string Base_Image_Name{"img_"};
    std::vector<image> image_vec;

    for (int i = 0; i < 10; ++i)
    {
        const std::string Image_Number = std::to_string(i);
        auto temp_ = Base_Image_Path + "/" + Base_Image_Name + Image_Number + ".csv";
        // std::cout << temp_ << std::endl;
        // std::ifstream file(temp_);
        // auto j = image{temp_};
        image_vec.push_back(std::move(image{temp_}));
    }

    // for (auto &ele : image_vec)
    // {
    //     ele.write_to_buffer(data::colour_data(10));
    //     std::cout << "----" << std::endl;
    // }

    return 0;
}