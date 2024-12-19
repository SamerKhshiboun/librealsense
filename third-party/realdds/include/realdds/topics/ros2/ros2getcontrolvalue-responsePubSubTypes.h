// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.


#ifndef _GET_CONTROL_VALUE_RESPONSE_PUBSUBTYPES_H_
#define _GET_CONTROL_VALUE_RESPONSE_PUBSUBTYPES_H_

#include <fastdds/dds/topic/TopicDataType.hpp>
#include <fastrtps/utils/md5.h>
#include "ros2getcontrolvalue-response.h"

#if !defined(GEN_API_VER) || (GEN_API_VER != 1)
#error Generated Header is not compatible with current installed Fast DDS. Please, regenerate it with fastddsgen.
#endif // GEN_API_VER

namespace realdds
{
    namespace topics
    {

        class GetControlValueResponsePubSubType : public eprosima::fastdds::dds::TopicDataType
        {
        public:
            typedef GetControlValueResponse type;

            eProsima_user_DllExport GetControlValueResponsePubSubType();
            eProsima_user_DllExport virtual ~GetControlValueResponsePubSubType() override;

            eProsima_user_DllExport bool serialize(void *data, eprosima::fastrtps::rtps::SerializedPayload_t *payload) override;
            eProsima_user_DllExport bool deserialize(eprosima::fastrtps::rtps::SerializedPayload_t *payload, void *data) override;
            eProsima_user_DllExport std::function<uint32_t()> getSerializedSizeProvider(void *data) override;
            eProsima_user_DllExport void *createData() override;
            eProsima_user_DllExport void deleteData(void *data) override;
            eProsima_user_DllExport bool getKey(void *data, eprosima::fastrtps::rtps::InstanceHandle_t *handle, bool force_md5 = false) override;

#ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
            eProsima_user_DllExport inline bool is_bounded() const override
            {
                return false;
            }

#endif // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

#ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
            eProsima_user_DllExport inline bool is_plain() const override
            {
                return false;
            }

#endif // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

#ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
            eProsima_user_DllExport inline bool construct_sample(
                void *memory) const override
            {
                (void)memory;
                return false;
            }

#endif // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        private:
            MD5 m_md5;
            unsigned char *m_keyBuffer;
        };

    } // namespace topics
} // namespace realdds

#endif
