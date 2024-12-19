// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.

#pragma once

#include <realdds/dds-defines.h>
#include <realdds/topics/ros2/ros2getcontrolvalue-response.h>

#include <memory>

namespace realdds
{
    namespace topics
    {
        class GetControlValueResponsePubSubType;
    } // namespace msg
} // namespace sensor_msgs

namespace realdds
{

    class dds_participant;
    class dds_topic;
    class dds_topic_reader;

    namespace topics
    {

        class GetControlValueResponseMsg
        {
        public:
            using type = realdds::topics::GetControlValueResponsePubSubType;

            GetControlValueResponseMsg() = default;
            ~GetControlValueResponseMsg() = default;

            long const get_result() const { return _data.get_result(); }
            void set_result(uint64_t new_result) { _data.set_result(new_result); }

            static std::shared_ptr<dds_topic> create_topic(std::shared_ptr<dds_participant> const &participant,
                                                           char const *topic_name);


        private:
            realdds::topics::GetControlValueResponse _data;
        };

    } // namespace topics
} // namespace realdds
