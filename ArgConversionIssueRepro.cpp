#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <utility>

namespace py = pybind11;
using namespace py::literals;

namespace {
    class Base
    {
    public:
        Base() = default;
    };

    class Derived : public Base
    {
    public:
        Derived() = default;
    };

    class Path
    {
    public:
        explicit Path(std::string  path)
            : m_path(std::move(path))
        {
        }

    private:
        const std::string m_path;
    };
}

PYBIND11_MODULE(arg_conversion_issue, m){
    py::class_<Base>(m, "Base")
    .def(py::init<>());

    py::class_<Derived, Base> derived(m, "Derived");
    derived.def(py::init<>())
    // Uncomment "__len__" below to see a further error, where pybind will invoke "__getitem__" of this class with index 0
    .def("__len__", [](const Derived& self) { return 1; })
    .def("__getitem__", [](const Derived& self, const std::string& key){ return py::none(); });

    py::class_<Path>(m, "Path")
    .def(py::init<std::string>());

    // In the codebase where I found this issue the implicit cast was necessary to trigger the issue
    // But in this minimal example the issue also appears without it
    // py::implicitly_convertible<std::string, Path>();
    // using PathType = Path;
    using PathType = std::string;

    m.def("the_issue",
        [](const std::vector<Base>& inputs, const PathType& path) {return inputs; },
        "inputs"_a.noconvert(),  // This does not help because the failure is already in the first "no-convert" pass
        "path"_a
    );
    m.def("the_issue", [](const Derived& inputs, const PathType& path) {return inputs; });

    // A fix is to manually remove sq_item to make PySequence_Check fail on Derived instances
    // reinterpret_cast<PyTypeObject*>(derived.ptr())->tp_as_sequence->sq_item = nullptr;
}
