cmake_minimum_required(VERSION 3.10)

project(hybrid-synthesis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
  )
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp")

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

add_library(reskel STATIC ${SOURCES})

add_executable(hybrid-synthesis "${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp")
target_link_libraries(hybrid-synthesis reskel)
