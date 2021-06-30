cmake_minimum_required(VERSION 3.10)

project(reskel)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
  )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

install(TARGETS ${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include
  FILES_MATCHING PATTERN "*.h")

enable_testing()
add_subdirectory(unittest)
