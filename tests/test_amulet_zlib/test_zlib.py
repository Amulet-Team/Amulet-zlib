from unittest import TestCase

from amulet.zlib import (
    ZipBombException,
    throw_zipbomb_exported,
    catch_zipbomb_exported,
    catch_runtime_exported,
    throw_zipbomb_static,
    catch_zipbomb_static,
    catch_runtime_static,
)

from test_amulet_zlib.test_zlib_ import (
    throw_zipbomb_test,
    catch_zipbomb_test,
    catch_runtime_test,
    throw_zipbomb_import,
    catch_zipbomb_import,
    catch_runtime_import,
)


def throw_zipbomb_py_1():
    raise ZipBombException


def throw_zipbomb_py_2():
    raise ZipBombException("throw_zipbomb_py_2")


def catch_zipbomb_py(func):
    try:
        func()
    except ZipBombException:
        return True
    except Exception:
        return False
    return False


def catch_runtime_py(func):
    try:
        func()
    except RuntimeError:
        return True
    except Exception:
        return False
    return False


class ZlibTest(TestCase):
    def test_exceptions(self) -> None:
        for throw in (
            throw_zipbomb_exported,
            throw_zipbomb_static,
            throw_zipbomb_test,
            throw_zipbomb_import,
            # throw_zipbomb_py_1,
            # throw_zipbomb_py_2,
        ):
            for catch in (
                catch_zipbomb_exported,
                catch_runtime_exported,
                catch_zipbomb_static,
                catch_runtime_static,
                catch_zipbomb_test,
                catch_runtime_test,
                catch_zipbomb_import,
                catch_runtime_import,
                catch_zipbomb_py,
                catch_runtime_py,
            ):
                with self.subTest(throw=throw.__name__, catch=catch.__name__):
                    self.assertTrue(catch(throw))
