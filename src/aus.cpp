// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#include "types.h"
#include "aus.h"
#include <fstream>

#define NOT_SUPPORTED(func_api)  func_api##{throw std::runtime_error("function " #func_api " is not supported without BUILD_AUS flag on");}
#ifdef BUILD_AUS

namespace librealsense
{
    static aus_data aus_data_obj;
}

void librealsense::aus_set(std::string counter, int value)
{
    aus_data_obj.set(counter, value);
}

void librealsense::aus_increment(std::string counter)
{
    aus_data_obj.increment(counter);
}

void librealsense::aus_decrement( std::string counter )
{
    aus_data_obj.decrement( counter );
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

void librealsense::aus_start(std::string timer)
{
    aus_data_obj.start(timer);
}

void librealsense::aus_stop(std::string timer)
{
    aus_data_obj.stop(timer);
}

long librealsense::aus_get(std::string counter)
{
    return aus_data_obj.get(counter);
}


std::vector<std::string> librealsense::aus_get_counters_list()
{
   return aus_data_obj.get_counters_list();
}

void librealsense::aus_on_device_changed(std::shared_ptr<device_interface> device)
{
    aus_data_obj.on_device_changed(device);
}

void librealsense::aus_system_counter_increment(std::string suffix, std::string device_name)
{
    std::string counter_name = librealsense::aus_build_system_counter_name(suffix, device_name);
    librealsense::aus_increment(counter_name);
}

void librealsense::aus_system_timer_start(std::string suffix, std::string device_name)
{
    std::string timer_name = aus_build_system_timer_name(suffix, device_name);
    librealsense::aus_start(timer_name);
}


#else // BUILD_AUS

NOT_SUPPORTED(void librealsense::aus_set(std::string counter, int value));
NOT_SUPPORTED(void librealsense::aus_increment(std::string counter));
NOT_SUPPORTED(void librealsense::aus_decrement(std::string counter));
NOT_SUPPORTED(void librealsense::aus_start(std::string timer));
NOT_SUPPORTED(void librealsense::aus_stop(std::string timer));
NOT_SUPPORTED(std::string librealsense::aus_build_system_timer_name(std::string suffix, std::string device_name));
NOT_SUPPORTED(std::string librealsense::aus_build_system_counter_name(std::string suffix, std::string device_name));
NOT_SUPPORTED(long librealsense::aus_get(std::string counter));
NOT_SUPPORTED(std::vector<std::string> librealsense::aus_get_counters_list());
NOT_SUPPORTED(void librealsense::aus_system_counter_increment(std::string suffix, std::string device_name));
NOT_SUPPORTED(void librealsense::aus_system_timer_start(std::string suffix, std::string device_name));

void librealsense::aus_on_device_changed(std::shared_ptr<device_interface> device)
{
    return;
}

#endif // BUILD_AUS
