# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2022 Intel Corporation. All Rights Reserved.

# test:device D400*
import sys

import pyrealsense2 as rs
from rspy import devices, log, test, file, repo


#############################################################################################
# Tests
#############################################################################################

test.start("TEST: NO_DEVICES_ATTACHED")
try:
    connected_devices = rs.aus_get_counter("RS2_AUS_CONNECTED_DEVICES")
    test.check_equal(connected_devices, 0)

    used_devices = rs.aus_get_counter("RS2_AUS_USED_DEVICES")
    test.check_equal(connected_devices, 0)

    used_filters = rs.aus_get_counter("RS2_AUS_USED_FILTERS")
    test.check_equal(used_filters, 0)

    # run_time = rs.get_run_time_aus()
    # test.check()
except:
    test.unexpected_exception()
test.finish()

#############################################################################################

test.print_results_and_exit()
