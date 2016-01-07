cmake_minimum_required(VERSION 3.4.1)
project(Terra)

set (BOOST_LIBS boost_system boost_filesystem)
set (SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)
set (YAML_LIBS yaml-cpp)
set (GCC_FLAGS "-std=c++11")

# Add flags
add_definitions(${GCC_FLAGS})

# Project header files
include_directories(inc inc/components inc/processes)

# Project Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create Executable 
add_executable(terra ${SOURCES})

# Linked Libraries
target_link_libraries(terra ${BOOST_LIBS} ${SFML_LIBS} ${YAML_LIBS})
