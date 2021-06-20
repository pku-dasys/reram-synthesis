cmake_minimum_required(VERSION 3.10)

project(hybrid-synthesis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
  )
include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

add_executable(hybrid-synthesis ${SOURCES})
