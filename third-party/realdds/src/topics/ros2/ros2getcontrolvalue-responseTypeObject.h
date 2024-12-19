// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023-4 Intel Corporation. All Rights Reserved.

#ifndef _GET_CONTROL_VALUE_REQUEST_TYPE_OBJECT_H_
#define _GET_CONTROL_VALUE_REQUEST_TYPE_OBJECT_H_

#include <fastrtps/types/TypeObject.h>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif
#else
#define eProsima_user_DllExport
#endif

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(GETCONTROLREQUEST_SOURCE)
#define GETCONTROLREQUEST_DllAPI __declspec( dllexport )
#else
#define GETCONTROLREQUEST_DllAPI __declspec( dllimport )
#endif // GETCONTROLREQUEST_SOURCE
#else
#define GETCONTROLREQUEST_DllAPI
#endif
#else
#define GETCONTROLREQUEST_DllAPI
#endif // _WIN32

using namespace eprosima::fastrtps::types;

eProsima_user_DllExport void registerHeaderTypes();


namespace realdds {
namespace topics {

eProsima_user_DllExport void registerGetControlValueRequestTypes();

} // namespace topics
} // namespace realdds

#endif