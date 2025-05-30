#include <pybind11/pybind11.h>

#include <amulet/pybind11_extensions/compatibility.hpp>

#include <amulet/zlib/zlib.hpp>

namespace py = pybind11;
namespace pyext = Amulet::pybind11_extensions;

void init_module(py::module& m)
{
    pyext::init_compiler_config(m);

    m.def("decompress_zlib_gzip", [](py::bytes src){
        std::string dst;
        {
            py::gil_scoped_release nogil;
            Amulet::zlib::decompress_zlib_gzip(src, dst);
        }
        return py::bytes(dst);
    });
    m.def("compress_zlib", [](py::bytes src){
        std::string dst;
        {
            py::gil_scoped_release nogil;
            Amulet::zlib::compress_zlib(src, dst);
        }
        return py::bytes(dst);
    });
    m.def("compress_gzip", [](py::bytes src){
        std::string dst;
        {
            py::gil_scoped_release nogil;
            Amulet::zlib::compress_gzip(src, dst);
        }
        return py::bytes(dst);
    });
}

PYBIND11_MODULE(_amulet_zlib, m)
{
    m.def("init", &init_module);
}
