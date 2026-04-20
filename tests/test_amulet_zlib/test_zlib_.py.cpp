#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include <amulet/zlib/zlib.hpp>

namespace py = pybind11;

static void throw_zipbomb_test(){
    throw Amulet::zlib::ZipBombException("test");
}

static bool catch_zipbomb_test(std::function<void()> func){
    try {
        func();
    }
    catch (const Amulet::zlib::ZipBombException&){
        return true;
    }
    catch (...){
        return false;
    }
    return false;
}

static bool catch_runtime_test(std::function<void()> func){
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

static void throw_zipbomb_import(){
    return Amulet::zlib::throw_zipbomb_exported();
}

static bool catch_zipbomb_import(std::function<void()> func){
    return Amulet::zlib::catch_zipbomb_exported(func);
}

static bool catch_runtime_import(std::function<void()> func){
    return Amulet::zlib::catch_runtime_exported(func);
}

void init_test_amulet_zlib(py::module m_parent)
{
    auto m = m_parent.def_submodule("test_zlib_");

    m.def("throw_zipbomb_test", &throw_zipbomb_test);
    m.def("catch_zipbomb_test", &catch_zipbomb_test);
    m.def("catch_runtime_test", &catch_runtime_test);
    m.def("throw_zipbomb_import", &throw_zipbomb_import);
    m.def("catch_zipbomb_import", &catch_zipbomb_import);
    m.def("catch_runtime_import", &catch_runtime_import);
}
