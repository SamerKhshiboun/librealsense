// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#ifndef LIBREALSENSE_RS2_AUS_HPP
#define LIBREALSENSE_RS2_AUS_HPP

#include "rs.h"
#include "hpp/rs_types.hpp"

namespace rs2
{
 
    inline void aus_set(const char* counter, int value = 0)
    {
        rs2_error* e = nullptr;
        rs2_aus_set(counter, value, &e);
        error::handle(e);
    }

    inline void aus_increase(const char* counter)
    {
        rs2_error* e = nullptr;
        rs2_aus_increase(counter, &e);
        error::handle(e);
    }

    inline int aus_get_counter(const char* counter)
    {
        rs2_error* e = nullptr;
        int result = rs2_aus_get_counter(counter, &e);
        error::handle(e);
        return result;
    }

    inline void aus_start_timer(const char* timer)
    {
        rs2_error* e = nullptr;
        rs2_aus_start_timer(timer, &e);
        error::handle(e);
    }

    inline void aus_stop_timer(const char* timer)
    {
        rs2_error* e = nullptr;
        rs2_aus_stop_timer(timer, &e);
        error::handle(e);
    }

    inline rs2_time_t aus_get_timer(const char* timer)
    {
        rs2_error* e = nullptr;
        rs2_time_t result = rs2_aus_get_timer(timer, &e);
        error::handle(e);
        return result;
    }

    inline std::vector<std::string> aus_get_counters_names()
    {
        rs2_error* e = nullptr;
        auto buffer = rs2_aus_get_counters_names(&e);
        std::shared_ptr<const rs2_aus_counters_names> list(buffer, rs2_aus_delete_counters_names);
        error::handle(e);

        auto size = rs2_aus_get_counters_names_size(list.get(), &e);
        error::handle(e);

        std::vector<std::string> results;
        for (size_t i = 0; i < size; ++i) {
            const char* item_cstr = rs2_aus_get_counter_name_data(list.get(), i, &e);
            error::handle(e);
            results.push_back(item_cstr);
        }

        return results;
    }

}

#endif // LIBREALSENSE_RS2_AUS_HPP
