cmake_minimum_required(VERSION 3.16)

project(example)

find_package(Boost COMPONENTS thread chrono REQUIRED)

include_directories(${Boost_INCLUDE_DIRS}) 

add_executable(${CMAKE_PROJECT_NAME} main.cpp trace.cpp)

message("Boost_INCLUDE_DIRS: '${Boost_INCLUDE_DIRS}'")
message("Boost_THREAD_LIBRARY: '${Boost_THREAD_LIBRARY}'")
message("Boost_LIBRARIES: '${Boost_LIBRARIES}'")

target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
