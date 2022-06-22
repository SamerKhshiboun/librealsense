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


test.start("Test test counters")
try:
    print("SAMER BEFORE")
    counters_list = rs.aus_get_counters_names()
    print(counters_list)
    print("SAMER AFTER")
    expected_counters_dict = \
        {
            'RS2_AUS_COLORIZER_FILTER_INIT': 1,
            'RS2_AUS_CONNECTED_DEVICES': 2,
            'RS2_AUS_COLORIZER_FILTER_PROCESSED_FRAMES': 10
        }
    print(counters_list)
    test.check_equal_lists(expected_counters_dict.keys(), counters_list)

    for counter_name in expected_counters_dict:
        aus_val = rs.aus_get_counter(counter_name)
        expected_val = expected_counters_dict[counter_name]
        test.check_equal(expected_val, aus_val)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################
# FINISH TESTS

test.print_results_and_exit()