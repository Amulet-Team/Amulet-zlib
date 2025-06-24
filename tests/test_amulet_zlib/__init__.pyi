from __future__ import annotations

import faulthandler as _faulthandler

from . import _test_amulet_zlib, test_zlib_

__all__ = ["compiler_config", "test_zlib_"]

def _init() -> None: ...

compiler_config: dict
