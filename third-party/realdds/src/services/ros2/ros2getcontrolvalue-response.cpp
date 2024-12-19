// File: ros2getcontrolvalue.cpp

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.

#include "realdds/services/ros2/ros2getcontrolvalue-response.h"
#include "ros2getcontrolvalue-responseTypeObject.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

namespace realdds
{
    namespace services
    {

        size_t GetControlValueResponse::getMaxCdrSerializedSize(
            size_t current_alignment)
        {
            size_t initial_alignment = current_alignment;

            current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + 255 + 1;

            return current_alignment - initial_alignment;
        }

        size_t GetControlValueResponse::getCdrSerializedSize(
            const GetControlValueResponse &data,
            size_t current_alignment)
        {
            (void)data;
            size_t initial_alignment = current_alignment;
            current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + sizeof(data.result) + 1;
            return current_alignment - initial_alignment;
        }

        void GetControlValueResponse::serialize(
            eprosima::fastcdr::Cdr &scdr) const
        {

            scdr << result;
        }

        void GetControlValueResponse::deserialize(
            eprosima::fastcdr::Cdr &dcdr)
        {
            dcdr >> result;
        }

        size_t GetControlValueResponse::getKeyMaxCdrSerializedSize(
            size_t current_alignment)
        {
            size_t current_align = current_alignment;

            return current_align;
        }

        bool GetControlValueResponse::isKeyDefined()
        {
            return false;
        }

        void GetControlValueResponse::set_result(long new_result)
        {
            result = new_result;
        }

        long GetControlValueResponse::get_result() const
        {
            return result;
        }

    } // namespace topics
} // namespace realdds
