// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
#if BUILD_AUS
    struct aus_data
    {
        string cmd;
        string librealsense_version;
        int start_time;
        int end_time;
        int connected_cameras_count;
        int used_cameras_count;
        int colorizer_filter_count;
        int align_depth_filter_count;
        int pointcloud_filter_count;


        aus_data() {}

        void print_aus_data() const {
            std::cout << "aus_data print function" << std::endl;
        }
    };
#else
    struct aus_data
    {
        void print_aus_data() const {
            std::cout << "should build with cmake flag" << std::endl;
        }

    };
#endif
}