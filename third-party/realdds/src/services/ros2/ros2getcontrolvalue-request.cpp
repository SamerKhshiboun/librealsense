// File: ros2getcontrolvalue.cpp

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.

#include "realdds/services/ros2/ros2getcontrolvalue-request.h"
#include "ros2getcontrolvalue-requestTypeObject.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

namespace realdds
{
    namespace services
    {

        size_t GetControlValueRequest::getMaxCdrSerializedSize(
            size_t current_alignment)
        {
            size_t initial_alignment = current_alignment;

            current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + 255 + 1;

            return current_alignment - initial_alignment;
        }

        size_t GetControlValueRequest::getCdrSerializedSize(
            const GetControlValueRequest &data,
            size_t current_alignment)
        {
            (void)data;
            size_t initial_alignment = current_alignment;
            current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + sizeof(data.control_id) + 1;
            return current_alignment - initial_alignment;
        }

        void GetControlValueRequest::serialize(
            eprosima::fastcdr::Cdr &scdr) const
        {

            scdr << control_id;
        }

        void GetControlValueRequest::deserialize(
            eprosima::fastcdr::Cdr &dcdr)
        {
            dcdr >> control_id;
        }

        size_t GetControlValueRequest::getKeyMaxCdrSerializedSize(
            size_t current_alignment)
        {
            size_t current_align = current_alignment;

            return current_align;
        }

        bool GetControlValueRequest::isKeyDefined()
        {
            return false;
        }

        void GetControlValueRequest::set_control_id(uint64_t new_control_id)
        {
            control_id = new_control_id;
        }
        
        uint64_t GetControlValueRequest::get_control_id() const
        {
            return control_id;
        }

    } // namespace topics
} // namespace realdds
