// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.

#ifndef _GET_CONTROL_VALUE_RESPONSE_H_
#define _GET_CONTROL_VALUE_RESPONSE_H_

#include <fastrtps/utils/fixed_size_string.hpp>
#include <stdint.h>

#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec(dllexport)
#else
#define eProsima_user_DllExport
#endif // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(GETCONTROLRESPONSE_SOURCE)
#define GETCONTROLRESPONSE_DllAPI __declspec(dllexport)
#else
#define GETCONTROLRESPONSE__DllAPI __declspec(dllimport)
#endif // 
#else
#define GETCONTROLRESPONSE__DllAPI
#endif // EPROSIMA_USER_DLL_EXPORT
#else
#define GETCONTROLRESPONSE__DllAPI
#endif // _WIN32

namespace eprosima
{
    namespace fastcdr
    {
        class Cdr;
    } // namespace fastcdr
} // namespace eprosima

namespace realdds
{
    namespace services
    {

        class GetControlValueResponse
        {
        public:
            // Default constructor
            eProsima_user_DllExport GetControlValueResponse() = default;

            // Default constructor
            eProsima_user_DllExport ~GetControlValueResponse() = default;

            eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
                size_t current_alignment = 0);

            /*!
             * @brief This function returns the serialized size of a data depending on the buffer alignment.
             * @param data Data which is calculated its serialized size.
             * @param current_alignment Buffer alignment.
             * @return Serialized size.
             */
            eProsima_user_DllExport static size_t getCdrSerializedSize(
                const realdds::services::GetControlValueResponse &data,
                size_t current_alignment = 0);

            /*!
             * @brief This function serializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serialize(
                eprosima::fastcdr::Cdr &cdr) const;

            /*!
             * @brief This function deserializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void deserialize(
                eprosima::fastcdr::Cdr &cdr);

            /*!
             * @brief This function returns the maximum serialized size of the Key of an object
             * depending on the buffer alignment.
             * @param current_alignment Buffer alignment.
             * @return Maximum serialized size.
             */
            eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
                size_t current_alignment = 0);

            /*!
             * @brief This function tells you if the Key has been defined for this type
             */
            eProsima_user_DllExport static bool isKeyDefined();

            /*!
             * @brief This function serializes the key members of an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serializeKey(
                eprosima::fastcdr::Cdr &cdr) const;

            eProsima_user_DllExport void set_result(long new_result);
            eProsima_user_DllExport long get_result() const;

        private:
            long result;
        };

    } // namespace topics
} // namespace realdds

#endif
