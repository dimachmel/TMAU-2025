cmake_minimum_required(VERSION 3.14)
project(temperature_model_as06521)

set(CMAKE_CXX_STANDARD 17)

# Main program
add_executable(temperature_model_as06521 
    main.cpp 
    temperature_model.cpp
)

# Tests
enable_testing()

# Download and setup GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(temperature_model_test_as06521 
    ../test/temperature_model_test.cpp 
    temperature_model.cpp
)

target_include_directories(temperature_model_test_as06521 PRIVATE .)
target_link_libraries(temperature_model_test_as06521 
    gtest 
    gtest_main
)

# FIXED: Use add_test instead of gtest_discover_tests
add_test(
    NAME TemperatureModelTest_as06521
    COMMAND temperature_model_test_as06521
)

# Code coverage
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(temperature_model_test_as06521 PRIVATE --coverage)
    target_link_libraries(temperature_model_test_as06521 PRIVATE gcov)
endif()
