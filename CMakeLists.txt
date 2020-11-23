cmake_minimum_required(VERSION 3.4.1)
project(Terra)

set (SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)
set (YAML_LIBS yaml-cpp )
set (BOOST_LIBS boost_system boost_filesystem)
set (GCC_FLAGS "-O3 -std=c++11")
set (THREAD_STUFF pthread  X11)

# Add flags
add_definitions(${GCC_FLAGS})

# Project header files
include_directories(inc inc/components inc/processes)
include_directories(/usr/X11R6/include /usr/local/Cellar/yaml-cpp/0.6.3_1/include)

# Project Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create Executable 
add_executable(terra ${SOURCES})

# Linked Libraries
target_link_libraries(terra -L/usr/X11R6/lib
-L/usr/local/Cellar/yaml-cpp/0.6.3_1/lib -L/usr/local/Cellar/boost/1.74.0/lib)
target_link_libraries(terra ${SFML_LIBS} ${YAML_LIBS} ${BOOST_LIBS} ${THREAD_STUFF} )

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
include_directories(${SFML_INCLUDE_DIR}) 
target_link_libraries(terra ${SFML_LIBRARIES})
endif()
