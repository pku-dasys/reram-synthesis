cmake_minimum_required(VERSION 3.10)

project(sha3.test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} reskel)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
set_tests_properties(${PROJECT_NAME}
    PROPERTIES PASS_REGULAR_EXPRESSION "cycle 8986\nbbox 2815 170")

