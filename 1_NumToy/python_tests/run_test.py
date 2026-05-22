"""
Test Entry Point
"""

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD_DIR = ROOT / "cmake-build-debug"

sys.path.insert(0, str(BUILD_DIR))

from main_core import MainCore

if __name__ == '__main__':
    main_module = MainCore()
    main_module()