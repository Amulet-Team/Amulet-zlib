#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_test_amulet_zlib(py::module);

static void _init_test_amulet_zlib(py::module m){
    init_test_amulet_zlib(m);
}

PYBIND11_MODULE(_test_amulet_zlib, m) {
    m.def("init", &_init_test_amulet_zlib, py::arg("m"));
}
