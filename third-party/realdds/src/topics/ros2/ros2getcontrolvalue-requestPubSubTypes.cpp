// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.

#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>

#include "realdds/topics/ros2/ros2getcontrolvalue-requestPubSubTypes.h"

using SerializedPayload_t = eprosima::fastrtps::rtps::SerializedPayload_t;
using InstanceHandle_t = eprosima::fastrtps::rtps::InstanceHandle_t;


namespace realdds {
namespace topics {

GetControlValueRequestPubSubType::GetControlValueRequestPubSubType()
{
    //SAMER
    setName("std_srvs::srv::dds_::Empty2_Request_");
    m_typeSize = 4 + 8; // Encapsulation + long field size
    m_isGetKeyDefined = false;
    m_keyBuffer = nullptr;
}

GetControlValueRequestPubSubType::~GetControlValueRequestPubSubType()
{
    if (m_keyBuffer != nullptr)
    {
        free(m_keyBuffer);
    }
}

bool GetControlValueRequestPubSubType::serialize(void* data, eprosima::fastrtps::rtps::SerializedPayload_t* payload)
{
    GetControlValueRequest* p_type = static_cast<GetControlValueRequest*>(data);

    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
    eprosima::fastcdr::Cdr ser(fastbuffer);

    payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    ser.serialize_encapsulation();

    try
    {
        ser << p_type->get_control_id();
    }
    catch (eprosima::fastcdr::exception::NotEnoughMemoryException&)
    {
        return false;
    }

    payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
    return true;
}

bool GetControlValueRequestPubSubType::deserialize(eprosima::fastrtps::rtps::SerializedPayload_t* payload, void* data)
{
    try
    {

        GetControlValueRequest *p_type = static_cast<GetControlValueRequest *>(data);

        eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char *>(payload->data), payload->length);
        eprosima::fastcdr::Cdr deser(fastbuffer);

        deser.read_encapsulation();
        payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

        // Deserialize the object.
        p_type->deserialize(deser);
    }
    catch (eprosima::fastcdr::exception::NotEnoughMemoryException &)
    {
        return false;
    }

    return true;
}

std::function<uint32_t()> GetControlValueRequestPubSubType::getSerializedSizeProvider(void* data)
{
    return [data]() -> uint32_t
    {
        return static_cast<uint32_t>(8 + 4); // long field + encapsulation
    };
}

void* GetControlValueRequestPubSubType::createData()
{
    return new GetControlValueRequest();
}

void GetControlValueRequestPubSubType::deleteData(void* data)
{
    delete static_cast<GetControlValueRequest*>(data);
}

bool GetControlValueRequestPubSubType::getKey(void* data, eprosima::fastrtps::rtps::InstanceHandle_t* handle, bool force_md5)
{
    (void)data;
    (void)handle;
    (void)force_md5;
    return false;
}

} // namespace topics
} // namespace realdds
