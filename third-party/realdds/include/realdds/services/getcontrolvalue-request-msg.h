// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.

#pragma once

#include <realdds/dds-defines.h>
#include <realdds/services/ros2/ros2getcontrolvalue-request.h>

#include <memory>

namespace realdds
{
    namespace services
    {
        class GetControlValueRequestPubSubType;
    } // namespace msg
} // namespace sensor_msgs

namespace realdds
{

    class dds_participant;
    class dds_topic;
    class dds_topic_reader;

    namespace services
    {

        class GetControlValueRequestMsg
        {
        public:
            using type = realdds::services::GetControlValueRequestPubSubType;

            GetControlValueRequestMsg() = default;
            ~GetControlValueRequestMsg() = default;

            uint64_t const get_control_id() const { return _data.get_control_id(); }
            void set_control_id(uint64_t new_control_id) { _data.set_control_id(new_control_id); }

            static std::shared_ptr<dds_topic> create_service(std::shared_ptr<dds_participant> const &participant,
                                                           char const *topic_name);


        private:
            realdds::services::GetControlValueRequest _data;
        };

    } // namespace topics
} // namespace realdds
