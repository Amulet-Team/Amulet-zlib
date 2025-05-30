#include <pybind11/pybind11.h>

#include <string>
#include <string_view>

#include <amulet/zlib/zlib.hpp>

#include <amulet/test_utils/test_utils.hpp>

namespace py = pybind11;

void init_test_zlib(py::module m_parent)
{
    auto m = m_parent.def_submodule("test_zlib_");

    m.def("test_cpp_zlib", []() {
        std::string src(100000000, 0);
        std::string compressed = "helloworld";
        Amulet::zlib::compress_zlib(src, compressed);

        // test original is preserved
        ASSERT_EQUAL(std::string, "helloworld", compressed.substr(0, 10))
        ASSERT_LESS(size_t, 10, compressed.size())

        std::string decompressed;
        Amulet::zlib::decompress_zlib_gzip(std::string_view(compressed).substr(10), decompressed);
        ASSERT_EQUAL(std::string, src, decompressed)
    });

    m.def("test_cpp_gzip", []() {
        std::string src(100000000, 0);
        std::string compressed = "helloworld";
        Amulet::zlib::compress_gzip(src, compressed);

        // test original is preserved
        ASSERT_EQUAL(std::string, "helloworld", compressed.substr(0, 10))
        ASSERT_LESS(size_t, 10, compressed.size())

        std::string decompressed;
        Amulet::zlib::decompress_zlib_gzip(std::string_view(compressed).substr(10), decompressed);
        ASSERT_EQUAL(std::string, src, decompressed)
    });

    m.def("test_cpp_zip_bomb", []() {
        std::string src(100100000, 0);
        std::string compressed;
        Amulet::zlib::compress_zlib(src, compressed);

        std::string decompressed;
        ASSERT_RAISES(Amulet::zlib::ZipBombException, Amulet::zlib::decompress_zlib_gzip(compressed, decompressed))
    });
}
