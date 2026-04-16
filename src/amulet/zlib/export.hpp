#pragma once

#ifndef AMULET_ZLIB_EXPORT
    #ifdef _WIN32
        #ifdef ExportAmuletZlib
            #define AMULET_ZLIB_EXPORT __declspec(dllexport)
        #else
            #define AMULET_ZLIB_EXPORT __declspec(dllimport)
        #endif
    #else
        #define AMULET_ZLIB_EXPORT
    #endif
#endif

#if !defined(AMULET_ZLIB_EXPORT_EXCEPTION)
    #if defined(__GNUC__) || defined(__clang__)
        #define AMULET_ZLIB_EXPORT_EXCEPTION __attribute__((visibility("default")))
    #else
        #define AMULET_ZLIB_EXPORT_EXCEPTION
    #endif
#endif
