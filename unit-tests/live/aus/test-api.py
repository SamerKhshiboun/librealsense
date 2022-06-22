# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2022 Intel Corporation. All Rights Reserved.

from time import sleep

import pyrealsense2 as rs
from rspy import devices, log, test, file, repo


#############################################################################################
# Tests
#############################################################################################

test.start("Test set without parameters (default value 0)")
try:
    rs.aus_set("USER_COUNTER_1")
    user_counter_1 = rs.aus_get_counter("USER_COUNTER_1")
    test.check_equal(user_counter_1, 0)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test set with parameter")
try:
    rs.aus_set("USER_COUNTER_2", 5)
    user_counter_2 = rs.aus_get_counter("USER_COUNTER_2")
    test.check_equal(user_counter_2, 5)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test increasing an already defined parameter")
try:
    rs.aus_set("USER_COUNTER_3")
    for n in range(10):
        rs.aus_increase("USER_COUNTER_3")
    user_counter_3 = rs.aus_get_counter("USER_COUNTER_3")
    test.check_equal(user_counter_3, 10)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test increasing a new parameter")
try:
    for n in range(10):
        rs.aus_increase("USER_COUNTER_4")
    user_counter_4 = rs.aus_get_counter("USER_COUNTER_4")
    test.check_equal(user_counter_4, 10)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test set of an already defined parameter")
try:
    rs.aus_set("USER_COUNTER_4")
except:
    test.finish()
else:
    test.unexpected_exception()

#############################################################################################

test.start("Test timer (start, stop, get)")
try:
    rs.aus_start_timer("TEST_TIMER")
    sleep(3)
    rs.aus_stop_timer("TEST_TIMER")
    test_timer = rs.aus_get_timer("TEST_TIMER")
    test.check(test_timer >= 3)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("Test get counters names list")
try:
    counters_list = rs.aus_get_counters_names()
    expected_list = ['USER_COUNTER_1', 'USER_COUNTER_2', 'USER_COUNTER_3', 'USER_COUNTER_4', 'TEST_TIMER']
    test.check_equal_lists(expected_list, counters_list)
except:
    test.unexpected_exception()
test.finish()

#############################################################################################
# FINISH TESTS

test.print_results_and_exit()
