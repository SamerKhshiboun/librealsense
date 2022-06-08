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

void librealsense::aus_init()
{
    std::cout << "librealsense::aus_init" << std::endl;
}

void librealsense::aus_print()
{
    aus_data_obj.print_data();
}

void librealsense::aus_declare_counter(std::string counter)
{
    aus_data_obj.declare_counter(counter);
}

void librealsense::aus_increase_counter(std::string counter)
{
    aus_data_obj.increase_counter(counter);
}

int librealsense::aus_get_counter(std::string counter)
{
    return aus_data_obj.get_counter(counter);
}

#else // BUILD_AUS

void librealsense::aus_init()
{
    throw std::runtime_error("aus_init is not supported without BUILD_AUS");
}

void librealsense::aus_print()
{
    throw std::runtime_error("aus_print is not supported without BUILD_AUS");
}

void librealsense::aus_increase_counter(std::string counter)
{
    throw std::runtime_error("aus_increase_counter is not supported without BUILD_AUS");
}

int librealsense::aus_get_counter(std::string counter)
{
    throw std::runtime_error("aus_get_counter is not supported without BUILD_AUS");
}

#endif // BUILD_AUS

