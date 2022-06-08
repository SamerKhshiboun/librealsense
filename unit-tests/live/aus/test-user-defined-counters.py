# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2022 Intel Corporation. All Rights Reserved.

# test:device D400*
import sys

import pyrealsense2 as rs
from rspy import devices, log, test, file, repo


#############################################################################################
# Tests
#############################################################################################

test.start("TEST: USER_DEFINED_COUNTERS - define counter with declare_counter")
try:
    rs.declare_counter_aus("USER_COUNTER_1")
    user_counter_1 = rs.get_counter_aus("USER_COUNTER_1")
    test.check_equal(user_counter_1, 0)

    rs.increase_counter_aus("USER_COUNTER_1")
    test.check_equal(user_counter_1, 1)

    for n in range(10):
        rs.increase_counter_aus("USER_COUNTER_1")
    user_counter_1 = rs.get_counter_aus("USER_COUNTER_1")
    test.check_equal(user_counter_1, 11)



except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.start("TEST: USER_DEFINED_COUNTERS - define counter with increase_counter")
try:
    rs.aus_increase_counter("USER_COUNTER_1")
    user_counter_1 = rs.aus_get_counter("USER_COUNTER_1")
    test.check_equal(user_counter_1, 1)

    rs.increase_counter_aus("USER_COUNTER_1")
    test.check_equal(user_counter_1, 2)

    for n in range(10):
        rs.aus_get_counter("USER_COUNTER_1")
    user_counter_1 = rs.aus_get_counter("USER_COUNTER_1")
    test.check_equal(user_counter_1, 12)

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
    test.unexpected_exception()
test.finish()

#############################################################################################

test.print_results_and_exit()
