#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "image.hpp"
#include "filters.hpp"

int main()
{
    const std::string Base_Origin_Image_Path{"./original_images"};
    const std::string Base_Image_Name{"img_"};
    std::vector<image> image_vec;
    

    for (int i = 0; i < 10; ++i)
    {
        const std::string Image_Number = std::to_string(i);
        const std::string temp_ = Base_Origin_Image_Path + "/" + Base_Image_Name + Image_Number + ".csv";
        // std::cout << temp_ << std::endl;
        image_vec.push_back(image{temp_});
        // std::cout << "2" << std::endl;
    }

    

#if 1
    int red_channel_enhance[]{100, 0, 0};
    int green_channel_enhance[]{0, 100, 0};
    int blue_channel_enhance[]{0, 0, 100};
    int brightness_enhance[]{100, 100, 100};
    int darkness_enhance_1[]{-50, -50, -50};
    int darkness_enhance_2[]{-25, -25, -25};
    int free_style_enhance[]{15, 45, -10};

    image_vec[0].add_filter(new filters::channel_adjustment(darkness_enhance_1))
                .add_filter(new filters::grey_scale())
                .add_filter(new filters::gamma_correction(0.5))
                .add_filter(new filters::sepia());

    image_vec[1].add_filter(new filters::grey_scale())
                .add_filter(new filters::channel_adjustment(darkness_enhance_1))
                .add_filter(new filters::negative())
                .add_filter(new filters::sepia());

    image_vec[2].add_filter(new filters::grey_scale())
                .add_filter(new filters::contrast(40))
                .add_filter(new filters::channel_adjustment(darkness_enhance_2))
                .add_filter(new filters::sepia())
                .add_filter(new filters::gamma_correction(3));

    image_vec[3].add_filter(new filters::grey_scale())
                .add_filter(new filters::sepia())
                .add_filter(new filters::gamma_correction(2))
                .add_filter(new filters::channel_adjustment(red_channel_enhance));

    image_vec[4].add_filter(new filters::negative())
                .add_filter(new filters::channel_adjustment(darkness_enhance_2))
                .add_filter(new filters::sepia())
                .add_filter(new filters::contrast(60));

    image_vec[5].add_filter(new filters::sepia())
                .add_filter(new filters::gamma_correction(0.5))
                .add_filter(new filters::channel_adjustment(brightness_enhance));

    image_vec[6].add_filter(new filters::contrast(25))
                .add_filter(new filters::channel_adjustment(free_style_enhance))
                .add_filter(new filters::grey_scale())
                .add_filter(new filters::sepia())
                .add_filter(new filters::channel_adjustment(darkness_enhance_2));

    image_vec[7].add_filter(new filters::sepia())
                .add_filter(new filters::gamma_correction(10))
                .add_filter(new filters::contrast(20))
                .add_filter(new filters::negative());

    image_vec[8].add_filter(new filters::channel_adjustment(green_channel_enhance))
                .add_filter(new filters::channel_adjustment(blue_channel_enhance))
                .add_filter(new filters::gamma_correction(0.5))
                .add_filter(new filters::contrast(25));

    image_vec[9].add_filter(new filters::grey_scale())
                .add_filter(new filters::contrast(10))
                .add_filter(new filters::channel_adjustment(brightness_enhance))
                .add_filter(new filters::gamma_correction(0.1));


    auto start = std::chrono::high_resolution_clock::now();
    // for(int i = 0; i < 100; ++i)
        for (auto &image : image_vec)
        {
            image.render();
        }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time for Object Oriented Design Technique: " << elapsed.count() << " s\n";

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