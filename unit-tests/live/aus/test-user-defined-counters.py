# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2022 Intel Corporation. All Rights Reserved.

# test:device D400*
import sys
from time import sleep

import pyrealsense2 as rs
from rspy import devices, log, test, file, repo


#############################################################################################
# Tests
#############################################################################################

print(rs.aus_print_stats())
test.start("TEST: USER_DEFINED_COUNTERS - define counter with declare_counter")
try:
    rs.aus_init()
    rs.aus_declare_counter("USER_COUNTER_1")
    user_counter_1 = rs.aus_get_counter("USER_COUNTER_1")
    test.check_equal(user_counter_1, 0)

    rs.aus_increase_counter("USER_COUNTER_1")
    test.check_equal(user_counter_1, 1)

    for n in range(10):
        rs.aus_increase_counter("USER_COUNTER_1")
    user_counter_1 = rs.aus_get_counter("USER_COUNTER_1")
    test.check_equal(user_counter_1, 11)

except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("TEST: USER_DEFINED_COUNTERS - define counter with increase_counter")
try:
    rs.aus_increase_counter("USER_COUNTER_2")
    user_counter_2 = rs.aus_get_counter("USER_COUNTER_2")
    test.check_equal(user_counter_2, 1)

    rs.aus_increase_counter("USER_COUNTER_2")
    test.check_equal(user_counter_2, 2)

    for n in range(10):
        rs.aus_get_counter("USER_COUNTER_2")
    user_counter_2 = rs.aus_get_counter("USER_COUNTER_2")
    test.check_equal(user_counter_2, 12)

except:
    test.unexpected_exception()
test.finish()

#############################################################################################


#############################################################################################

test.start("TEST: USER_DEFINED_COUNTERS - declare an already declared counter ")
try:
    rs.aus_declare_counter("USER_COUNTER_1")
    rs.aus_declare_counter("USER_COUNTER_1")
except:
    test.finish()
test.unexpected_exception()
#############################################################################################
sleep(10)
print(rs.aus_print_stats())
test.print_results_and_exit()
