#include <iostream>
#include <string>

#include "data.hpp"

int main() {
    const std::string Base_Image_Path{"./Img"};
    const std::string Base_Image_Name{"img_"};
    for (int i = 0; i < 10; ++i) {
        const std::string Image_Number = std::to_string(i);
        auto temp_ = Base_Image_Path + "/" + Base_Image_Name + Image_Number + ".csv";
        std::cout << temp_ << std::endl;
        // std::ifstream file(temp_);
    }



    return 0;
}