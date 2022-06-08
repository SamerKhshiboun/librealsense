// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
    struct RS2_UNION_AUS_VALUE {
        enum { t_invalid, t_int, t_time, t_string} type_id;
        union
        {
            int _counter;
            std::time_t _time;
            std::string _str;
        };
        RS2_UNION_AUS_VALUE(int counter = 0) : type_id{ t_int }, _counter{ counter } {}
        RS2_UNION_AUS_VALUE(std::string str) : type_id{t_string}, _str{str} {}
        RS2_UNION_AUS_VALUE(std::time_t time) : type_id{ t_time }, _time{ time } {}

        ~RS2_UNION_AUS_VALUE()
        {
            switch (type_id)
            {
            case t_int:
            case t_time:
                // trivially destructible, no need to do anything
                break;
            case t_string:
                _str.~basic_string();
                break;
            case t_invalid:
                // do nothing
                break;
            default:
                throw std::runtime_error("unknown type");
            }
        }
        RS2_UNION_AUS_VALUE(const RS2_UNION_AUS_VALUE& other)
        {
            type_id = other.type_id;
            switch (type_id) {
            case t_invalid:
                break;
            case t_string:
                new (&_str) std::string();
                _str = other._str;
                break;
            case t_int:
                _counter = other._counter;
                break;
            case t_time:
                _time = other._time;
                break;
            }
        }
        RS2_UNION_AUS_VALUE& operator=(RS2_UNION_AUS_VALUE& other) {
            if (this == &other)
                return *this;
            return RS2_UNION_AUS_VALUE(other);
        }
    };

    typedef struct RS2_UNION_AUS_VALUE RS2_AUS_VALUE;



#ifdef BUILD_AUS


    class aus_data
    {
    public:
        aus_data()
        {
            _mp[version] = RS2_AUS_VALUE("2.5.0");
            _mp[start_time_str] = RS2_AUS_VALUE(std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now()));

        }

        void print_data() const {
            std::time_t start_time = _mp.at(start_time_str)._time;
            std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::time_t total_run_time = start_time - end_time;
            std::cout << " start time " << start_time << std::endl;
            std::cout << " end time " << end_time << std::endl;
            std::cout << " run time " << total_run_time << std::endl;
        }

        void declare_counter(std::string key)
        {
            if (_mp.find(key) != _mp.end())
            {
                throw std::runtime_error("counter already exists");
            }
            _mp[key] = RS2_AUS_VALUE();
        }

        void increase_counter(std::string key)
        {
            if (_mp.find(key) != _mp.end())
            {
                _mp[key]._counter++;
            }
            else
            {
                _mp[key] = RS2_AUS_VALUE(1);
            }
        }

        int get_counter(std::string key)
        {
            if (_mp.find(key) == _mp.end())
            {
                return 0;
            }
            return _mp[key]._counter;
        }

    private:
        std::unordered_map<std::string, RS2_AUS_VALUE> _mp;
        std::string version = "VERSION";
        std::string start_time_str = "START_TIME";
    };// class aus_Data

#else
    class aus_data
    {

    public:
        void print_data() const 
        {
            std::cout << "print_data() not working - should build with cmake flag" << std::endl;
        }

        void increase_counter(std::string key)
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