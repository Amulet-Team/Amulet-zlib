#pragma once

#include <stdexcept>
#include <functional>

#include <amulet/zlib/export.hpp>

namespace Amulet {
namespace zlib {

    class AMULET_ZLIB_EXPORT_EXCEPTION ZipBombException : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
        virtual ~ZipBombException();
    };

    AMULET_ZLIB_EXPORT void throw_zipbomb_exported();

    AMULET_ZLIB_EXPORT bool catch_zipbomb_exported(std::function<void()> func);
    AMULET_ZLIB_EXPORT bool catch_runtime_exported(std::function<void()> func);

} // namespace zlib
} // namespace Amulet
