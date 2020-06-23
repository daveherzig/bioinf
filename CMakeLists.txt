#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# Copyright 2020, David Herzig (dave.herzig@gmail.com)
#

cmake_minimum_required (VERSION 2.8.12.2 FATAL_ERROR)

set (PROJECT_NAME "bioinformatics library C++" CXX)
project (${PROJECT_NAME})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
SET (CMAKE_C_FLAGS “-Wall -std=c++14 -fvisibility=hidden -fvisibility-inlines-hidden”)


find_package (Boost 1.55.0 REQUIRED COMPONENTS system filesystem log log_setup thread)
find_package (Threads)

include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

if (Boost_FOUND)
  add_executable(bioinf bioinf.cpp filereader.cpp filewriter.cpp log.cpp test.cpp util.cpp debrujin.cpp)
  target_link_libraries(bioinf ${Boost_LIBRARIES} Threads::Threads)
endif ()
