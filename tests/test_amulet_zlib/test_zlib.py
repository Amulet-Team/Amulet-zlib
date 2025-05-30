from unittest import TestCase
import zlib
import gzip
import os

from amulet.zlib import (
    ZipBombException,
    get_max_decompression_size,
    set_max_decompression_size,
    decompress_zlib_gzip,
    compress_zlib,
    compress_gzip,
)

from test_amulet_zlib.test_zlib_ import test_cpp_zlib, test_cpp_gzip, test_cpp_zip_bomb


class ZlibTest(TestCase):
    def test_zlib_compress(self) -> None:
        src = os.urandom(10_000_000)
        compressed = compress_zlib(src)
        self.assertEqual(src, zlib.decompress(compressed))

    def test_zlib_decompress(self) -> None:
        src = os.urandom(10_000_000)
        compressed = zlib.compress(src)
        self.assertEqual(src, decompress_zlib_gzip(compressed))

    def test_gzip_compress(self) -> None:
        src = os.urandom(10_000_000)
        compressed = compress_gzip(src)
        self.assertEqual(src, gzip.decompress(compressed))

    def test_gzip_decompress(self) -> None:
        src = os.urandom(10_000_000)
        compressed = gzip.compress(src)
        self.assertEqual(src, decompress_zlib_gzip(compressed))

    def test_zip_bomb_false(self) -> None:
        src = b"\x00" * 100_000_000
        compressed_gzip = gzip.compress(src)
        compressed_zlib = zlib.compress(src)
        self.assertEqual(src, decompress_zlib_gzip(compressed_gzip))
        self.assertEqual(src, decompress_zlib_gzip(compressed_zlib))

    def test_zip_bomb_true(self) -> None:
        # to trigger the zip bomb error it must be at least one chunk size larger than the configured size
        src = b"\x00" * 100_100_000
        compressed_gzip = gzip.compress(src)
        compressed_zlib = zlib.compress(src)
        with self.assertRaises(ZipBombException):
            decompress_zlib_gzip(compressed_gzip)
        with self.assertRaises(ZipBombException):
            decompress_zlib_gzip(compressed_zlib)

        self.assertEqual(100_000_000, get_max_decompression_size())
        set_max_decompression_size(100_100_000)
        self.assertEqual(100_100_000, get_max_decompression_size())

        self.assertEqual(src, decompress_zlib_gzip(compressed_gzip))
        self.assertEqual(src, decompress_zlib_gzip(compressed_zlib))

        set_max_decompression_size(100_000_000)
        self.assertEqual(100_000_000, get_max_decompression_size())

    def test_cpp_zlib(self) -> None:
        test_cpp_zlib()

    def test_cpp_gzip(self) -> None:
        test_cpp_gzip()

    def test_cpp_zip_bomb(self) -> None:
        test_cpp_zip_bomb()
