
cmake_minimum_required(VERSION 3.8)

project(SmartCalc_2_0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        SmartCalc_2_0_tests
        tests/test_calc.cc
        backend/model/parseString.cc
        backend/model/postfixNotation.cc
        backend/model/calculatePostfix.cc
)

target_link_libraries(
        SmartCalc_2_0_tests
        GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(SmartCalc_2_0_tests)