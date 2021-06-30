cmake_minimum_required(VERSION 3.10)

project(dotprod.test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} reskel)

