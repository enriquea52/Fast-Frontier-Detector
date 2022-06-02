cmake_minimum_required(VERSION 3.0.2)
project(frontier_detector)

find_package(catkin REQUIRED COMPONENTS
    pybind11_catkin)

catkin_package(
    LIBRARIES
    CATKIN_DEPENDS pybind11_catkin
)

include_directories(${catkin_INCLUDE_DIRS})

pybind_add_module(frontier_detector MODULE modules/main.cpp)


catkin_install_python(PROGRAMS scripts/frontier_detection.py
                      DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(TARGETS frontier_detector
  LIBRARY DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
