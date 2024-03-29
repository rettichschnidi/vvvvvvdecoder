CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(vvvvvvdecoder)

#Set the version of vvvvvvdecoder
set(VERSION 0.0.1)

#Exit if someone tries to contaminates the source directory with an in-source build
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message (FATAL_ERROR "Please do out-of-source builds.\nTo cleanup: \"rm -rf CMake CMakeCache.txt  CMakeFiles/\"")
endif()

OPTION(DEBUG "Build a debug version" ON)
IF(DEBUG)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3 -ggdb")
ELSE()
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O6 -s -fomit-frame-pointer -Wno-deprecated" )
ENDIF()

OPTION(EXIT_ON_WARNING "Cancel the bulid process if a warning shows up" ON)
IF(EXIT_ON_WARNING)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
ENDIF()

OPTION(PRINT_ALL_WARNINGS "Show all compiler warnings" ON)
IF(PRINT_ALL_WARNINGS)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
ENDIF()

#Place all executables in bin/, libraries in /lib
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# as recommended here:
# http://www.vtk.org/Wiki/CMake:Eclipse_UNIX_Tutorial#Parsing_Errors_more_efficiently
IF(CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

# as recommended here:
# http://www.vtk.org/Wiki/CMake:Eclipse_UNIX_Tutorial#Automatic_Discovery_of_Include_directories_.28Optional.2C_but_handy.29
SET(CMAKE_VERBOSE_MAKEFILE ON)

FIND_PACKAGE(Boost 1.44 REQUIRED filesystem program_options)

ADD_EXECUTABLE(vvvvvvdecoder vvvvvvdecoder.cpp)
TARGET_LINK_LIBRARIES(vvvvvvdecoder ${Boost_LIBRARIES})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
