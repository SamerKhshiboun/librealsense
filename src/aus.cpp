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

void librealsense::aus_set_counter(std::string counter, int val)
{
    aus_data_obj.set_counter(counter, val);
}

void librealsense::aus_increase_counter(std::string counter)
{
    aus_data_obj.increase_counter(counter);
}


std::string librealsense::aus_build_system_timer_name(std::string suffix, std::string device_name)
{
    std::string result = "RS2_AUS_";
    if (device_name != "")
    {
        result += device_name + "_";
    }
    result += suffix + "_TIMER";
    std::replace(result.begin(), result.end(), ' ', '_');
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string librealsense::aus_build_system_counter_name(std::string suffix, std::string device_name)
{
    std::string result = "RS2_AUS_";
    if (device_name != "")
    {
        result += device_name + "_";
    }
    result += suffix + "_COUNTER";
    std::replace(result.begin(), result.end(), ' ', '_');
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

void librealsense::aus_start_timer(std::string timer)
{
    aus_data_obj.start_timer(timer);
}

void librealsense::aus_stop_timer(std::string timer)
{
    aus_data_obj.stop_timer(timer);
}

int librealsense::aus_get_counter(std::string counter)
{
    return aus_data_obj.get_counter(counter);
}

rs2_time_t librealsense::aus_get_timer(std::string timer)
{
    return aus_data_obj.get_timer(timer);
}

std::vector<std::string> librealsense::aus_get_counters_names()
{
   return aus_data_obj.get_counters_names();
}

std::vector<std::string> librealsense::aus_get_timers_names()
{
    return aus_data_obj.get_timers_names();
}

#else // BUILD_AUS


void librealsense::aus_set_counter(std::string counter, int val)
{
    throw std::runtime_error("aus_print_stats is not supported without BUILD_AUS");
}

void librealsense::aus_increase_counter(std::string counter)
{
    throw std::runtime_error("aus_increase is not supported without BUILD_AUS");
}

void librealsense::aus_start_timer(std::string timer)
{
    throw std::runtime_error("aus_start_timer is not supported without BUILD_AUS");
}

void librealsense::aus_stop_timer(std::string timer)
{
    throw std::runtime_error("aus_stop_timer is not supported without BUILD_AUS");
}

std::string librealsense::aus_build_system_timer_name(std::string suffix, std::string device_name)
{
    throw std::runtime_error("aus_build_system_timer_name is not supported without BUILD_AUS");
}

std::string librealsense::aus_build_system_counter_name(std::string suffix, std::string device_name)
{
    throw std::runtime_error("aus_build_system_counter_name is not supported without BUILD_AUS");
}

int librealsense::aus_get_counter(std::string counter)
{
    throw std::runtime_error("aus_get_counter is not supported without BUILD_AUS");
}

rs2_time_t librealsense::aus_get_timer(std::string timer)
{
    throw std::runtime_error("aus_get_timer is not supported without BUILD_AUS");
}

std::vector<std::string> librealsense::aus_get_counters_names()
{
    throw std::runtime_error("get_counters_names is not supported without BUILD_AUS");
}

std::vector<std::string> librealsense::aus_get_timers_names()
{
    throw std::runtime_error("aus_get_timers_names is not supported without BUILD_AUS");
}

#endif // BUILD_AUS

