# Root CMake configuration file for QtCity project
cmake_minimum_required(VERSION 3.18)
project(QtCity VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

set(CMAKE_PREFIX_PATH "C:/Qt/6.4.3/mingw_64")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(src)
