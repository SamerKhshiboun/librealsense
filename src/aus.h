// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
    

    union RS2_AUS_VALUE
    {
        constexpr RS2_AUS_VALUE() : counter(0) {}
        ~RS2_AUS_VALUE() {}
        int counter;
        std::time_t time;
        std::string str;
    };

#if BUILD_AUS
    class aus_data
    {
    public:
        void print_aus_data() const {
            std::cout << "aus_data print function" << std::endl;
        }

        void increase_counter(std::string key)
        {
            if (mp.find(key) != mp.end())
            {
                mp[key].counter++;
            }
            else {
                mp[key].counter = 1;
            }
        }

        int get_counter(std::string key)
        {
            if (mp.find(key) != mp.end())
            {
                return 0;
            }
            return mp[key].counter;
        }


    private:
        std::unordered_map<std::string, RS2_AUS_VALUE> mp;
    };// class aus_Data

#else
    class aus_data
    {

    public:
        void print_aus_data() const 
        {
            std::cout << "print_aus_data() not working - should build with cmake flag" << std::endl;
        }

        void increase_counter(RS2_AUS_FIELD field)
        {
            std::cout << "increase_counter(RS2_AUS_FIELD field) not working - should build with cmake flag" << std::endl;
        }

        int get_counter(std::string key)
        {
            std::cout << "get_counter(std::string key) not working - should build with cmake flag" << std::endl;
            return 0;
        }
    }; //class aus_data
#endif
 
}