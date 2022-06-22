// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
    typedef struct rs2_aus_timer_struct {
        rs2_time_t _start;
        rs2_time_t _end;
        bool _running;

        rs2_aus_timer_struct() : _start(0), _end(0), _running(false) { }

        void start()
        {
            if (_running) 
            {
                //throw std::runtime_error("AUS - Trying to start a running timer");
            }

            _start = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            _running = true;
        }

        void stop()
        {
            if (!_running)
            {
                return;
            }

            _end = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            _running = false;
        }

        
    } rs2_aus_timer;

    typedef struct rs2_aus_value_struct {

        enum { t_int, t_timer} type_id;
        union 
        {
            int _counter;
            rs2_aus_timer _timer;
        };

        rs2_aus_value_struct(int counter = 0) : type_id { t_int } , _counter{ counter } {}
        rs2_aus_value_struct(rs2_aus_timer timer) : type_id{ t_timer }, _timer{ timer } {}
        ~rs2_aus_value_struct()
        {
            switch (type_id)
            {
            case t_int:
            case t_timer:
                break;
            default:
                throw std::runtime_error("unknown type");
            }
        }

        rs2_aus_value_struct(const rs2_aus_value_struct& other)
        {
            type_id = other.type_id;
            switch (type_id) {
            case t_int:
                _counter = other._counter;
                break;
            case t_timer:
                _timer = other._timer;
                break;
            }
        }

    } rs2_aus_value;

#ifdef BUILD_AUS

    class aus_data
    {

    public:
        aus_data()
        {
            _start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            _librealsense_version = RS2_API_VERSION_STR;
        }

        void set(std::string key, int value = 0)
        {
            if (_counters_mp.find(key) != _counters_mp.end())
            {
                throw std::runtime_error("counter \"" + key + "\" already exists");
            }
            _counters_mp[key] = rs2_aus_value(value);
        }

        void increase(std::string key)
        {
            if (_counters_mp.find(key) != _counters_mp.end())
            {
                _counters_mp[key]._counter++;
            }
            else
            {
                _counters_mp[key] = rs2_aus_value(1);
            }
        }

        int get_counter(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                throw std::runtime_error("counter \"" + key + "\" does not exist");
            }
            return _counters_mp[key]._counter;
        }

        void start_timer(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                rs2_aus_timer timer;
                timer.start();
                _counters_mp[key] = rs2_aus_value(timer);
            }
            else
            {
                _counters_mp[key]._timer.start();
            }
        }

        void stop_timer(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end()) {
                throw std::runtime_error("timer \"" + key + "\" does not exist");
            }
            _counters_mp[key]._timer.stop();
        }

        rs2_time_t get_timer(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                throw std::runtime_error("timer \"" + key + "\" does not exist");
            }

            rs2_aus_timer timer = _counters_mp[key]._timer;

            if (timer._running)
            {
                rs2_time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                return current_time - timer._start;
            }
            else {
                return timer._end - timer._start;
            }
        }

        std::vector<std::string> get_counters_names()
        {
            std::vector<std::string> result;
            for (const auto& pair : _counters_mp) {
                result.push_back(pair.first);
            }
            return result;
        }

    private:
        std::unordered_map<std::string, rs2_aus_value> _counters_mp;
        rs2_time_t _start_time;
        std::string _librealsense_version;

    }; // end of class aus_data

#else
    class aus_data
    {
    public:

        void set(std::string key, int value)
        {
            throw std::runtime_error("set is not supported without BUILD_AUS");
        }

        int increase(std::string key)
        {
            throw std::runtime_error("increase is not supported without BUILD_AUS");
        }

        int get_counter(std::string key)
        {
            throw std::runtime_error("get_counter is not supported without BUILD_AUS");
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

        void get_counters() const
        {
            throw std::runtime_error("get_counters is not supported without BUILD_AUS");
        }

        rs2_time_t get_run_time() {
            throw std::runtime_error("get_run_time is not supported without BUILD_AUS");
        }

    }; // end of class aus_data

#endif
}