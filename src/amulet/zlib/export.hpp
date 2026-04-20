#pragma once
#include <exception>

#ifndef AMULET_ZLIB_EXPORT
    #ifdef _WIN32
        #ifdef ExportAmuletZlib
            #define AMULET_ZLIB_EXPORT __declspec(dllexport)
        #else
            #define AMULET_ZLIB_EXPORT __declspec(dllimport)
        #endif
    #else
        #define AMULET_ZLIB_EXPORT __attribute__((visibility("default")))
    #endif
#endif
