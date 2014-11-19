cmake_minimum_required(VERSION 2.6)
PROJECT(RobVision)

## QT ##
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Widgets)

## Boost ##
set (BOOST_LIBRARYDIR "C:/boost_1_56_0/lib64-msvc-12.0")
SET (Boost_FIND_REQUIRED TRUE)
SET (Boost_FIND_QUIETLY TRUE)
SET (Boost_DEBUG FALSE)
set (Boost_USE_MULTITHREADED TRUE)
set (Boost_USE_STATIC_LIBS TRUE)
SET (Boost_ADDITIONAL_VERSIONS "1.56" "1.56.0")
FIND_PACKAGE(Boost COMPONENTS  program_options )

## Gocator ##
SET(GOCATOR_DIR "C:/Gocator")
SET(GOCATOR_INCLUDE_DIR ${GOCATOR_DIR}/include)
SET(GOCATOR_LIBRARIES_DIR ${GOCATOR_DIR}/lib/win64/debug)

INCLUDE_DIRECTORIES( 
${CMAKE_CURRENT_BINARY_DIR} 
${CMAKE_CURRENT_SOURCE_DIR} 
${Boost_INCLUDE_DIRS}
${GOCATOR_INCLUDE_DIR}
)
LINK_DIRECTORIES(
${Boost_LIBRARY_DIRS}
${GOCATOR_LIBRARIES_DIR})
SET(GOCATOR_LIBRARIES Go2.lib)
file(GLOB_RECURSE SRC_FILES ./RobVision/*.cpp ./RobVisionSys/*.cpp ./RobArm/*.cpp)
ADD_EXECUTABLE(RobVis ${SRC_FILES})
TARGET_LINK_LIBRARIES(RobVis ${GOCATOR_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(RobVis Qt5::Widgets)
