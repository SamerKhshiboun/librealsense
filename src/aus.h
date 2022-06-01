// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
    
#if BUILD_AUS
    struct aus_data
    {
        std::string cmd;
        std::string librealsense_version;
        int start_time;
        int end_time;
        int connected_cameras_count;
        int used_cameras_count;
        int colorizer_filter_count;
        int align_depth_filter_count;
        int pointcloud_filter_count;

        aus_data() : cmd("cmd"), librealsense_version("2.5.0"), start_time(0), end_time(0), connected_cameras_count(0),
            used_cameras_count(0), colorizer_filter_count(0), align_depth_filter_count(0), pointcloud_filter_count(0)
        {
        }

        void print_aus_data() const {
            std::cout << "aus_data print function" << std::endl;
        }

        void increase_counter(RS2_AUS_FIELD field) {
            switch (field) {
            case RS2_AUS_CONNECTED_CAMERAS:
                connected_cameras_count++;
                break;
            case RS2_AUS_USED_CAMERAS:
                used_cameras_count++;
                break;
            default:
                break;
            }
        }
    };
#else
    struct aus_data
    {
        aus_data()
        {
            std::cout << "aus_data() not working - should build with cmake flag" << std::endl;
        }
        void print_aus_data() const 
        {
            std::cout << "print_aus_data() not working - should build with cmake flag" << std::endl;
        }

        void increase_counter(RS2_AUS_FIELD field) 
        {
            std::cout << "increase_counter(RS2_AUS_FIELD field) not working - should build with cmake flag" << std::endl;
        }

    };
#endif
}