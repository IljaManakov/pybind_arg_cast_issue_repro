cmake_minimum_required(VERSION 3.15)
project(pybind_arg_cast_issue_repro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(PYBIND11_FINDPYTHON ON)
#find_package(Python 3.10 REQUIRED EXACT COMPONENTS Interpreter Development)

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11
  GIT_TAG        a2e59f0e7065404b44dfe92a28aca47ba1378dc4 # release-2.13.6
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(arg_conversion_issue ArgConversionIssueRepro.cpp)
