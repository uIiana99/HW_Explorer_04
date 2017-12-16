cmake_minimum_required(VERSION 3.2.2)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/SimonRussia/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "ef53eaa092c18d1ae26299daa4ea84d0f1d979ef"
)

project(explorer)

hunter_add_package(Catch)
find_package(Catch CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS system filesystem date_time program_options)
find_package(Boost CONFIG REQUIRED system filesystem date_time program_options)

add_executable(explorer ${CMAKE_CURRENT_SOURCE_DIR}/sources/explorer.cpp)

target_include_directories(explorer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(explorer Catch::Catch Boost::system Boost::filesystem Boost::date_time Boost::program_options)

install(TARGETS explorer RUNTIME DESTINATION bin)
