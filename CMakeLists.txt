# if g++ is used, version 5.0 (or later) is required
#clear;clear;cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++-5 ..;make

cmake_minimum_required (VERSION 2.8) # not tested with previous versions

project (RFTR)


file (GLOB SOURCES "src/*.cpp")
add_library (SRCLIB ${SOURCES})

list (APPEND CMAKE_CXX_FLAGS "-std=c++11")
# after installation of wiringPi it said:
# "To compile programs with wiringPi, you need to add: -lwiringPi to your compile line(s)"
# but it works without...
#list (APPEND CMAKE_CXX_FLAGS "-lwiringPi")
# and it's not working... so here is an alternative
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED)
target_link_libraries(SRCLIB ${WIRINGPI_LIBRARIES})
target_link_libraries(SRCLIB ${CMAKE_THREAD_LIBS_INIT})

file (GLOB DEMOS "*demos/*.cpp")
FOREACH(demopath ${DEMOS})
    string(REGEX REPLACE "([^ ]*)/demos//" "" filename ${demopath})
    string(REPLACE ".cpp" "" demoname ${filename})
    add_executable(${demoname} ${demopath})
    TARGET_LINK_LIBRARIES(${demoname} SRCLIB)
ENDFOREACH(demopath)
