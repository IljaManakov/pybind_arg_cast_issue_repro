import sys
from pathlib import Path
sys.path.insert(0, (Path(__file__).parent / "cmake-build-debug").as_posix())

from arg_conversion_issue import the_issue, Derived

derived = Derived()
the_issue([derived], "some_path")  # works
the_issue(derived, "some_path")  # arg conversion in dispatch goes haywire
