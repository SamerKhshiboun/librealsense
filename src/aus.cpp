// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#include "types.h"
#include "aus.h"

#include <fstream>

#ifdef BUILD_AUS

namespace librealsense
{
    static aus_data aus_data_obj;
}


void librealsense::init_aus()
{
    std::cout << "librealsense::init_aus" << std::endl;
    /*aus_data_obj.cmd = "full_path_to_cmd";
    aus_data_obj.librealsense_version = "2.5.0";*/
}

void librealsense::print_aus()
{
    std::cout << "librealsense::print_aus" << std::endl;
    aus_data_obj.print_aus_data();
}

void librealsense::increase_counter_aus(std::string counter)
{
    std::cout << "librealsense::increase_counter_aus" << std::endl;
    aus_data_obj.increase_counter(counter);
}

int librealsense::get_counter_aus(std::string counter)
{
    std::cout << "librealsense::get_counter_aus" << std::endl;
    return aus_data_obj.get_counter(counter);
}

#else // BUILD_AUS

void librealsense::init_aus()
{
    throw std::runtime_error("init_aus is not supported without BUILD_AUS");
}

void librealsense::print_aus()
{
    throw std::runtime_error("print_aus is not supported without BUILD_AUS");
}

void librealsense::increase_counter_aus(std::string counter)
{
    throw std::runtime_error("increase_counter_aus is not supported without BUILD_AUS");
}

int librealsense::get_counter_aus(std::string counter)
{
    throw std::runtime_error("get_counter_aus is not supported without BUILD_AUS");
}

#endif // BUILD_AUS

