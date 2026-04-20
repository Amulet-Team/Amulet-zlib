#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include <amulet/zlib/zlib.hpp>

namespace py = pybind11;

static void throw_zipbomb_static(){
    throw Amulet::zlib::ZipBombException("test");
}

static bool catch_zipbomb_static(std::function<void()> func){
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

static bool catch_runtime_static(std::function<void()> func){
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

static void _init_amulet_zlib(py::module m)
{
    py::register_exception<Amulet::zlib::ZipBombException>(m, "ZipBombException", PyExc_RuntimeError);

    m.def("throw_zipbomb_exported", &Amulet::zlib::throw_zipbomb_exported);
    m.def("catch_zipbomb_exported", &Amulet::zlib::catch_zipbomb_exported);
    m.def("catch_runtime_exported", &Amulet::zlib::catch_runtime_exported);
    m.def("throw_zipbomb_static", &throw_zipbomb_static);
    m.def("catch_zipbomb_static", &catch_zipbomb_static);
    m.def("catch_runtime_static", &catch_runtime_static);
}

PYBIND11_MODULE(_amulet_zlib, m)
{
    m.def("init", &_init_amulet_zlib, py::arg("m"));
}
