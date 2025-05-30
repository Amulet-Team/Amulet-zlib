#include <pybind11/pybind11.h>

#include <amulet/zlib/zlib.hpp>

namespace py = pybind11;

void init_test_zlib(py::module m_parent){
    auto m = m_parent.def_submodule("test_zlib_");

}
