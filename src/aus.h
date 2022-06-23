// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
    
    class aus_timer {
    
    public:
        aus_timer() :  _start(0), _end(0), _is_running(false) { }

        void start()
        {
            _start = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            _is_running = true;
        }

        void stop()
        {
            if (!_is_running)
            {
                return;
            }

            _end = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            _is_running = false;
        }

        time_t get_start() 
        {
            return _start;
        }

        time_t get_end()
        {
            return _end;
        }

        bool is_running() 
        {
            return _is_running;
        }

        time_t get_runtime() 
        {
            if (_is_running)
            {
                return get_current_time() - _start;
            }
            else
            {
                return _end - _start;
            }
        }

    private:

        time_t _start;
        time_t _end;
        bool _is_running;

        time_t get_current_time() 
        {
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        }

    };

  

#ifdef BUILD_AUS

    class aus_data
    {

    public:
        aus_data()
        {
            _start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            _librealsense_version = RS2_API_VERSION_STR;
        }

        void set_counter(std::string key, int value = 0)
        {
            assert_exists_counter(key);
            _counters_mp[key] = value;
        }

        void increase_counter(std::string key)
        {
            if (_counters_mp.find(key) != _counters_mp.end())
            {
                _counters_mp[key]++;
            }
            else
            {
                _counters_mp[key] = 1;
            }
        }

        int get_counter(std::string key)
        {
            assert_exists_counter(key);
            return _counters_mp[key];
        }

        void start_timer(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                aus_timer timer;
                timer.start();
                _timers_mp[key] = timer;
            }
            else
            {
                _timers_mp[key].start();
            }
        }

        void stop_timer(std::string key)
        {
            assert_exists_timer(key);
            _timers_mp[key].stop();
        }

        rs2_time_t get_timer(std::string key)
        {
            assert_exists_timer(key);
            return _timers_mp[key].get_runtime();
        }

        std::vector<std::string> get_counters_names()
        {
            std::vector<std::string> result;
            for (const auto& pair : _counters_mp) {
                result.push_back(pair.first);
            }
            return result;
        }

        std::vector<std::string> get_timers_names()
        {
            std::vector<std::string> result;
            for (const auto& pair : _timers_mp) {
                result.push_back(pair.first);
            }
            return result;
        }

    private:
        std::unordered_map<std::string, int> _counters_mp;
        std::unordered_map<std::string, aus_timer> _timers_mp;
        rs2_time_t _start_time;
        std::string _librealsense_version;

        void assert_exists_counter(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                throw std::runtime_error("counter \"" + key + "\" does not exist");
            }
        }

        void assert_exists_timer(std::string key)
        {
            if (_timers_mp.find(key) == _timers_mp.end())
            {
                throw std::runtime_error("timer \"" + key + "\" does not exist");
            }
        }

    }; // end of class aus_data

#else
    class aus_data
    {
    public:

        void set_counter(std::string key, int value)
        {
            throw std::runtime_error("set is not supported without BUILD_AUS");
        }

        int increase_counter(std::string key)
        {
            throw std::runtime_error("increase is not supported without BUILD_AUS");
        }

        int get_counter(std::string key)
        {
            throw std::runtime_error("get is not supported without BUILD_AUS");
        }
        
        void start_timer(std::string key)
        {
            throw std::runtime_error("start_timer is not supported without BUILD_AUS");
        }

        void stop_timer(std::string key)
        {
            throw std::runtime_error("stop_timer is not supported without BUILD_AUS");
        }

        rs2_time_t get_timer(std::string timer)
        {
            throw std::runtime_error("get_timer is not supported without BUILD_AUS");
        }

        std::vector<std::string> get_counters_names()
        {
            throw std::runtime_error("get_counters_names is not supported without BUILD_AUS");
        }

        std::vector<std::string> get_timers_names()
        {
            throw std::runtime_error("get_timers_names is not supported without BUILD_AUS");
        }


    }; // end of class aus_data

#endif
}
