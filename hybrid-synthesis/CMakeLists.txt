cmake_minimum_required(VERSION 3.10)

project(reskel)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
  )
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp")

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_executable(${PROJECT_NAME}.demo "${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp")
target_link_libraries(${PROJECT_NAME}.demo ${PROJECT_NAME})

enable_testing()
add_subdirectory(unittest)
