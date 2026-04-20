#include <stdexcept>

#include <amulet/zlib/zlib.hpp>

namespace Amulet {
namespace zlib {

    ZipBombException::~ZipBombException(){}

    void throw_zipbomb_exported(){
        throw ZipBombException("throw_zipbomb_exported");
    }

    bool catch_zipbomb_exported(std::function<void()> func){
        try {
            func();
        }
        catch (const ZipBombException&){
            return true;
        }
        catch (...){
            return false;
        }
        return false;
    }

    bool catch_runtime_exported(std::function<void()> func){
        try {
            func();
        }
        catch (const std::runtime_error&){
            return true;
        }
        catch (...){
            return false;
        }
        return false;
    }

} // namespace zlib
} // namespace Amulet
