# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2022 Intel Corporation. All Rights Reserved.

# test:device L500*
import sys
from time import sleep

import pyrealsense2 as rs
from rspy import devices, log, test, file, repo


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


test.start("Test test counters names")
try:
    counters_list = rs.aus_get_counters_names()
    expected_counters_dict = \
        {
            'RS2_AUS_L500_CONNECTED_DEVICES': 1,
            'RS2_AUS_COLORIZER_FILTER_INIT': 2,
            'RS2_AUS_INTEL_REALSENSE_L515_UVC_STREAM_TIMER': 100,
            'RS2_AUS_CONNECTED_DEVICES': 1,
            'RS2_AUS_INTEL_REALSENSE_L515_SYNTHETIC_STREAM_TIMER': 100,
            'RS2_AUS_COLORIZER_FILTER_PROCESSED_FRAMES': 10,
            'RS2_AUS_INTEL_REALSENSE_L515_HID_STREAM_TIMER': 100
        }
    test.check_equal_lists(expected_counters_dict.keys(), counters_list)

except:
    test.unexpected_exception()
test.finish()


#############################################################################################

test.start("Test test counters values")

try:
    for counter_name in expected_counters_dict:
        if "TIMER" not in counter_name:
            aus_val = rs.aus_get_counter(counter_name)
            expected_val = expected_counters_dict[counter_name]
            print("counter_name:", counter_name, "aus_val:", aus_val, " expected_val:", expected_val)
            test.check_equal(expected_val, aus_val)
    print("Done")
except:
    test.unexpected_exception
test.finish()

#############################################################################################


test.start("Test test timers values")
try:
    for counter_name in expected_counters_dict:
        if "TIMER" in counter_name:
            aus_val = rs.aus_get_timer(counter_name)
            print("counter_name:", counter_name, "aus_val:", aus_val, " expected_val:", expected_val)
            test.check_equal(aus_val > 1)
    print("Done")
except:
    test.unexpected_exception
test.finish()

#############################################################################################
# FINISH TESTS

test.print_results_and_exit()