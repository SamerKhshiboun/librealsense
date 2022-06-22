# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2022 Intel Corporation. All Rights Reserved.

# test:device L500*

import pyrealsense2 as rs
from rspy import devices, log, test, file, repo
from time import sleep

#############################################################################################
# Tests
#############################################################################################

test.start("Init colorizer test")
try:
    pipeline = rs.pipeline()
    colorizer = rs.colorizer()
    pipeline.start()
    for i in range(10):
        frames = pipeline.wait_for_frames()
        depth_frame = frames.get_depth_frame()
        depth_color_frame = colorizer.colorize(depth_frame)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test counters names")
try:
    counters_list = rs.aus_get_counters_names()
    expected_counters_dict = \
        {
            'RS2_AUS_DEPTH_VISUALIZATION_COLORIZER_TIMER': -1,
            'RS2_AUS_INTEL_REALSENSE_L515_UVC_STREAM_TIMER': -1,
            'RS2_AUS_DEPTH_VISUALIZATION_COLORIZER_FILTER_INIT_COUNTER': 1,
            'RS2_AUS_INTEL_REALSENSE_L515_HID_STREAM_TIMER': -1,
            'RS2_AUS_CONNECTED_DEVICES_COUNTER': 1,
            'RS2_AUS_L500_CONNECTED_DEVICES_COUNTER': 1,
            'RS2_AUS_DEPTH_VISUALIZATION_COLORIZED_FRAMES_COUNTER': 10,
            'RS2_AUS_INTEL_REALSENSE_L515_SYNTHETIC_STREAM_TIMER': -1,
        }
    test.check_equal_lists(expected_counters_dict.keys(), counters_list)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test counters values")
try:
    for counter_name in expected_counters_dict.keys():
        if "TIMER" not in counter_name:
            aus_val = rs.aus_get_counter(counter_name)
            expected_val = expected_counters_dict[counter_name]
            test.check_equal(expected_val, aus_val)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test timers values")
try:
    sleep(3)
    my_list = expected_counters_dict.keys()
    for timer_name in my_list:
        if "TIMER" in timer_name:
            aus_val = rs.aus_get_timer(timer_name)
            test.check(aus_val >= 3)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.print_results_and_exit()
