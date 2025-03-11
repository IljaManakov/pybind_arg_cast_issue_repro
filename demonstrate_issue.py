import sys
import pathlib
sys.path.insert(0, (pathlib.Path(__file__).parent / "cmake-build-debug").as_posix())

from arg_conversion_issue import the_issue, Derived, Path

derived = Derived()
path = "some_path"

the_issue([derived], path)  # works
the_issue(derived, path)  # arg conversion in dispatcher goes haywire
