cmake_minimum_required(VERSION 3.10)

project(img-conv.test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} reskel)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
set_tests_properties(${PROJECT_NAME}
    PROPERTIES PASS_REGULAR_EXPRESSION "cycle 3774\nbbox 56607 510")

