# This file is part of HSCToSQL (Database converter).
# Copyright (c) 2022 Alexandr Shchukin
# Corresponding email: shchukin@ism.ac.ru
#
# HSCToSQL (Database converter) is free software:
# you can redistribute it and/or modify it under the terms
# of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# HSCToSQL (Database converter) is distributed in the hope that
# it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with HSCToSQL (Database converter).
# If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.14)

project(hsctosql LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Xml Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Xml Sql)

add_executable(hsctosql
  main.cpp
  database.h database.cpp
)

target_link_libraries(hsctosql Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(hsctosql Qt${QT_VERSION_MAJOR}::Xml)
target_link_libraries(hsctosql Qt${QT_VERSION_MAJOR}::Sql)
