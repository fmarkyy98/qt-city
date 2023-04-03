# Root CMake configuration file for QtCity project
cmake_minimum_required(VERSION 3.18)
project(QtCity VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(platforms)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
	Widgets 
	Core
)

message(${PROJECT_SOURCE_DIR})
message(${CMAKE_PREFIX_PATH})

add_subdirectory(src)
