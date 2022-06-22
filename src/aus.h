// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "types.h"

namespace librealsense
{
    typedef struct RS2_AUS_TIMER_STRUCT {
        rs2_time_t _start;
        rs2_time_t _end;
        bool _running;

        RS2_AUS_TIMER_STRUCT() : _start(0), _end(0), _running(false) { }

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

        //friend std::ostream& operator<<(std::ostream& os, RS2_AUS_TIMER_STRUCT const& arg)
        //{
        //    if (!arg._running) {
        //        os << "Timer has started at: " << arg._start << " and stopped at: " << arg._end;
        //        os << " Total Runtime = " << (arg._end - arg._start);
        //    }
        //    else {
        //        os << "Timer has started at: " << arg._start << " and is still running.";
        //    }
        //}

        //std::string to_string(RS2_AUS_TIMER_STRUCT const& arg)
        //{
        //    std::ostringstream ss;
        //    ss << arg;
        //    return std::move(ss).str();  // enable efficiencies in c++17
        //}


    } RS2_AUS_TIMER;

    typedef struct RS2_AUS_VALUE_STRUCT {

        enum { t_int, t_timer} type_id;
        union 
        {
            int _counter;
            RS2_AUS_TIMER _timer;
        };

        RS2_AUS_VALUE_STRUCT(int counter = 0) : type_id{ t_int }, _counter{ counter } {}
        RS2_AUS_VALUE_STRUCT(RS2_AUS_TIMER timer) : type_id{ t_timer }, _timer{ timer } {}
        ~RS2_AUS_VALUE_STRUCT()
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

        RS2_AUS_VALUE_STRUCT(const RS2_AUS_VALUE_STRUCT& other)
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

    } RS2_AUS_VALUE ;


#ifdef BUILD_AUS


    class aus_data
    {
    public:
        aus_data()
        {
            _start_time = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            _librealsense_version = RS2_API_VERSION_STR;
        }

        void set(std::string key, int value = 0)
        {
            if (_counters_mp.find(key) != _counters_mp.end())
            {
                throw std::runtime_error("counter already exists");
            }
            _counters_mp[key] = RS2_AUS_VALUE(value);
        }

        void increase(std::string key)
        {
            if (_counters_mp.find(key) != _counters_mp.end())
            {
                _counters_mp[key]._counter++;
            }
            else
            {
                _counters_mp[key] = RS2_AUS_VALUE(1);
            }
        }

        int get_counter(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                throw std::runtime_error("counter " + key + " does not exist");
            }
            return _counters_mp[key]._counter;
        }

        void start_timer(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                RS2_AUS_TIMER timer;
                timer.start();
                _counters_mp[key] = RS2_AUS_VALUE(timer);
            }
            else
            {
                _counters_mp[key]._timer.start();
            }
        }

        void stop_timer(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end()) {
                throw std::runtime_error("timer does not exist");
            }
            _counters_mp[key]._timer.stop();
        }

        rs2_time_t get_timer(std::string key)
        {
            if (_counters_mp.find(key) == _counters_mp.end())
            {
                throw std::runtime_error("timer does not exist");
            }

            RS2_AUS_TIMER timer = _counters_mp[key]._timer;

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
        std::unordered_map<std::string, RS2_AUS_VALUE> _counters_mp;
        rs2_time_t _start_time;
        std::string _librealsense_version;

        std::time_t _get_run_time() {
            rs2_time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            return current_time - _start_time;
        }

    }; // class aus_Data

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


    }; //class aus_data
#endif
 
}