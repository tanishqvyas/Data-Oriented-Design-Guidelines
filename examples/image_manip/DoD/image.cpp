// #include <iostream>
// #include <fstream>

// #include "image.hpp"

// image::image(const std::string &file_name) : image_file_{new std::fstream()},
//                                              height_{},
//                                              width_{},
//                                              filter_vec_{},
//                                              image_span_{}
// {
//     image_file_->open(file_name);

//     std::string line;
//     std::string pixel;

//     std::getline(*image_file_, line);
//     std::stringstream ss(line);

//     std::getline(ss, pixel, ',');
//     std::stringstream(pixel) >> height_;

//     std::getline(ss, pixel, ',');
//     std::stringstream(pixel) >> width_;

//     // std::cout << height_ << width_ << std::endl;
// }

// image::image(const image &obj) : image_file_{obj.image_file_},
//                                  height_{obj.height_},
//                                  width_{obj.width_},
//                                  filter_vec_{obj.filter_vec_},
//                                  image_span_{obj.image_span_}
// {
// }

// image &image::add_filter(filters::filter_types filter)
// {
//     filter_vec_.push_back(filter);
//     return *this;
// }

// data::pixel_colour_t *image::write_colours_to_buffer(
//     data::pixel_colour_t *nown_ptr)
// {
//     std::string line;
//     std::string str_pixel_value;
//     unsigned int ui_pixel_value;
//     unsigned int red_value;
//     unsigned int green_value;
//     unsigned int blue_value;

//     image_span_ = std::span<data::pixel_colour_t>{nown_ptr, height_ * width_};

//     for (auto &filter : filter_vec_)
//     {
//         std::visit([this](auto &f) {
//             // using T = std::decay_t<decltype(f)>;
//             // if constexpr (!std::is_same_v<T, std::monostate>)
//             f.set_span(image_span_);
//         },
//                    filter);
//     }

//     auto pixel = image_span_.begin();
//     while (std::getline(*image_file_, line))
//     {
//         std::stringstream ss(line);
//         while (std::getline(ss, str_pixel_value, ','))
//         {
//             assert((pixel != image_span_.end()));
//             std::stringstream(str_pixel_value) >> ui_pixel_value;

//             red_value = ui_pixel_value / 65536;
//             green_value = (ui_pixel_value % 65536) / 256;
//             blue_value = ui_pixel_value % 256;

// #if DEBUG
//             std::cout << red_value << ",";
//             std::cout << green_value << ",";
//             std::cout << blue_value << ",";
// #endif
//             std::get<0>(*pixel) = red_value;
//             std::get<1>(*pixel) = green_value;
//             std::get<2>(*pixel) = blue_value;

//             // std::cout << red_value << "," << green_value << "," << blue_value << std::endl;
//             // std::cout << std::get<0>(*pixel) << "," << std::get<1>(*pixel) << "," << std::get<2>(*pixel) << std::endl;

//             ++pixel;
//         }
//     }

// #if DEBUG
//     std::cout << std::endl;
//     for (auto &e : image_span_)
//     {
//         std::cout << std::get<0>(e) << ",";
//         std::cout << std::get<1>(e) << ",";
//         std::cout << std::get<2>(e) << ",";
//     }
//     std::cout << std::endl;
// #endif
//     return nown_ptr + height_ * width_; // pass back the pointer to the next location
// }

// template<std::size_t SIZE>
// std::size_t image::write_filters_to_buffer(std::array<filters::filter_types, SIZE>& filter_buffer, std::size_t free_index)  //std::span<filters::filter_types> filter_buffer, std::size_t free_index)
// {
//     for (auto &filter : filter_vec_)
//     {
//         filter_buffer[free_index] = filter;
//         ++free_index;
//     }
//     return free_index;
// }

// void image::write_back(const std::string &path_to_dest)
// {
//     std::cout << path_to_dest << std::endl;
//     unsigned int line_width_tracker = 0;
//     std::fstream destination_file;
//     destination_file.open(path_to_dest, std::fstream::out);
//     assert((destination_file.is_open()));
//     destination_file << height_ << "," << width_ << std::endl;
//     for (auto &pixel : image_span_)
//     {
//         ++line_width_tracker;
//         //  r*65536 + g*256 + b
//         unsigned int temp_ = std::get<0>(pixel) * 65536 +
//                              std::get<1>(pixel) * 256 +
//                              std::get<2>(pixel);
//         if (line_width_tracker == width_)
//         {
//             destination_file << temp_ << std::endl;
//             line_width_tracker = 0;
//         }
//         else
//         {
//             destination_file << temp_ << ",";
//         }
//     }

//     destination_file.close();
// }

// image::~image()
// {
// }