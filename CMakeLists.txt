CMAKE_MINIMUM_REQUIRED(VERSION 2.91.0)
PROJECT(LearningOpenGL)
message(${CMAKE_CXX_COMPILER})
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(cmake/3rdparty.cmake)
include(cmake/config.cmake)

set(EIGEN3_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/eigen)
find_package(Eigen3 REQUIRED)

SET( EXCUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/lib)

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include)
#INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/src/Hello)
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/src)
