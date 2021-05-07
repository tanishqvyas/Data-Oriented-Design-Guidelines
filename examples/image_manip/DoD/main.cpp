#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "image.hpp"
#include "filters.hpp"
#include "data.hpp"
#include "render_buffer.hpp"

int main()
{
    const std::string Base_Origin_Image_Path{"./original_images"};
    const std::string Base_Image_Name{"img_"};
    std::vector<image> image_vec;

    for (int i = 0; i < 10; ++i)
    {
        const std::string Image_Number = std::to_string(i);
        auto temp_ = Base_Origin_Image_Path + "/" + Base_Image_Name + Image_Number + ".csv";
        // std::cout << temp_ << std::endl;
        image_vec.push_back(image{temp_});
    }

    #if 1
    int red_channel_enhance[] {50, 0, 0};
    int green_channel_enhance[] {0, 50, 0};
    int blue_channel_enhance[] {0, 0, 50};
    int brightness_enhance[] {15, 5, 10};
    int darken_enhance[] {-15, -5, -10};

    image_vec[0].add_filter(filters::grey_scale())
                .add_filter(filters::contrast(50))
                .add_filter(filters::sepia());

    image_vec[1].add_filter(filters::sepia())
                .add_filter(filters::gamma_correction(6));

    image_vec[2].add_filter(filters::grey_scale())
                .add_filter(filters::contrast(40))
                .add_filter(filters::gamma_correction(3));

    image_vec[3].add_filter(filters::sepia())
                .add_filter(filters::gamma_correction(2))
                .add_filter(filters::channel_adjustment(red_channel_enhance))
                .add_filter(filters::channel_adjustment(blue_channel_enhance));

    image_vec[4].add_filter(filters::grey_scale())
                .add_filter(filters::sepia())
                .add_filter(filters::contrast(50));

    image_vec[5].add_filter(filters::sepia())
                .add_filter(filters::gamma_correction(5))
                .add_filter(filters::channel_adjustment(brightness_enhance));

    image_vec[6].add_filter(filters::sepia())
                .add_filter(filters::contrast(50))
                .add_filter(filters::channel_adjustment(darken_enhance));

    image_vec[7].add_filter(filters::sepia())
                .add_filter(filters::gamma_correction(3))
                .add_filter(filters::contrast(50))
                .add_filter(filters::negative());

    image_vec[8].add_filter(filters::channel_adjustment(green_channel_enhance))
                .add_filter(filters::channel_adjustment(darken_enhance));

    image_vec[9].add_filter(filters::grey_scale())
                .add_filter(filters::contrast(50));


    render_buffer buf(image_vec);
    
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; ++i)
        buf.render();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time for Data Oriented Design Technique: " << elapsed.count() << " s\n";

    #endif

    const std::string Base_Destination_Image_Path{"./modified_images"};

    for (int i = 0; i < 10; ++i)
    {
        const std::string Image_Number = std::to_string(i);
        auto temp_ = Base_Destination_Image_Path + "/" + Base_Image_Name + Image_Number + ".csv";
        // std::cout << temp_ << std::endl;
        image_vec[i].write_back(temp_);
    }

    // for (auto &ele : image_vec)
    // {
    //     ele.write_to_buffer(data::colour_data(10));
    //     std::cout << "----" << std::endl;
    // }

    return 0;
}