cmake_minimum_required(VERSION 3.14)

project(hsctosql LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Xml)

add_executable(hsctosql
  main.cpp
  database.h database.cpp
)

target_link_libraries(hsctosql Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(hsctosql Qt${QT_VERSION_MAJOR}::Xml)
