cmake_minimum_required(VERSION 2.8.3)
project(edline LANGUAGES CXX)


LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(pybind11_includes_dir)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")
add_definitions(-DCOMPILEDWITHC11)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# opencv
find_package(OpenCV REQUIRED)
find_package(pybind11 REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
	${pybind11_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
	${PYTHON_INCLUDE_DIRS}
)

link_directories(
  ${PROJECT_BINARY_DIR}/lib
)

add_subdirectory(src)
pybind11_add_module(edline src/edline_detector.cpp)
target_link_libraries(edline ${OpenCV_LIBS})
target_compile_definitions(edline PRIVATE VERSION_INFO=${VERSION_INFO})
