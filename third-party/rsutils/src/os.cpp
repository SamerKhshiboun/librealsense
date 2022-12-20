// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2017 Intel Corporation. All Rights Reserved.

#include <rsutils/os/os.h>

namespace rsutils
{
    std::string get_os_name()
    {
#ifdef _WIN32
        return "Windows";
#else
#ifdef __APPLE__
        return "Mac OS";
#else
#ifdef __linux__
        return "Linux";
#else
        return "Unknown";
#endif
#endif
#endif
    }  
}
