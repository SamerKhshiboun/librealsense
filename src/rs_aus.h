/* License: Apache 2.0. See LICENSE file in root directory.
   Copyright(c) 2022 Intel Corporation. All Rights Reserved. */

   /** \file rs_aus.h
   * \brief Exposes RealSense device functionality for C compilers
   */


#ifndef LIBREALSENSE_RS2_DEVICE_H
#define LIBREALSENSE_RS2_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rs_types.h"
#include "rs_sensor.h"

//AUS
void rs2_aus_set(const char* counter, int value, rs2_error** error);
void rs2_aus_increase(const char* counter, rs2_error** error);
int rs2_aus_get_counter(const char* counter, rs2_error** error);
void rs2_aus_start_timer(const char* timer, rs2_error** error);
void rs2_aus_stop_timer(const char* timer, rs2_error** error);
rs2_time_t rs2_aus_get_timer(const char* timer, rs2_error** error);
const rs2_aus_counters_names* rs2_aus_get_counters_names(rs2_error** error);

int rs2_get_aus_counters_names_size(const rs2_aus_counters_names* buffer, rs2_error** error);
void rs2_delete_aus_counters_names(const rs2_aus_counters_names* buffer);
const char** rs2_get_aus_counters_names_data(const rs2_aus_counters_names* buffer, rs2_error** error);
const char* rs2_get_aus_counter_name_data(const rs2_aus_counters_names* buffer, int i, rs2_error** error);

#ifdef __cplusplus
}
#endif
#endif

