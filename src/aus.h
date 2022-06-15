// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
    typedef struct RS2_AUS_VALUE_STRUCT {

        enum { t_int, t_time, t_string} type_id;
        union
        {
            int _counter;
            std::time_t _time;
            std::string _str;
        };

        RS2_AUS_VALUE_STRUCT(int counter = 0) : type_id{ t_int }, _counter{ counter } {}
        RS2_AUS_VALUE_STRUCT(std::string str) : type_id{t_string}, _str{str} {}
        RS2_AUS_VALUE_STRUCT(std::time_t time) : type_id{ t_time }, _time{ time } {}
        ~RS2_AUS_VALUE_STRUCT()
        {
            switch (type_id)
            {
            case t_int:
            case t_time:
                break;
            case t_string:
                _str.~basic_string();
                break;
            default:
                throw std::runtime_error("unknown type");
            }
        }

        RS2_AUS_VALUE_STRUCT(const RS2_AUS_VALUE_STRUCT& other)
        {
            type_id = other.type_id;
            switch (type_id) {
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

        RS2_AUS_VALUE_STRUCT& operator=(RS2_AUS_VALUE_STRUCT& other) {
            if (this == &other)
                return *this;
            return RS2_AUS_VALUE_STRUCT(other);
        }

    } RS2_AUS_VALUE ;


#ifdef BUILD_AUS


    class aus_data
    {
    public:
        aus_data()
        {
            _start_time = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            _mp[start_time_str] = RS2_AUS_VALUE(_start_time);
            _mp[version_str] = RS2_AUS_VALUE(_librealsense_version);
        }

        void print_stats()
        {
            int total_counters = _mp.size() - 2;
            std::time_t run_time = _get_run_time();
            std::cout << "total run time: "  << run_time << std::endl;
            std::cout << "total counters: " << total_counters << std::endl;
            std::cout << "librealsense version: " << _librealsense_version << std::endl;
            for (auto& key  : _mp) {
                auto it = _mp.find(key);
                if (it != _mp.end())
                    return it->second;
            }
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
        std::string version_str = "VERSION";
        std::string start_time_str = "START_TIME";
        std::time_t _start_time;
        std::string _librealsense_version = "2.50.0";

        std::time_t _get_run_time() {
            std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            return current_time - _start_time;
        }

    }; // class aus_Data

#else
    class aus_data
    {

    public:
        void print_stats() const 
        {
            std::cout << "print_stats() not working - should build with cmake flag" << std::endl;
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

        std::time_t get_run_time() {
            std::cout << "get_run_time() not working - should build with cmake flag" << std::endl;
            return 0;
        }

    }; //class aus_data
#endif
 
}