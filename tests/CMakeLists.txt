include(FetchContent)

# Download Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# MSVC compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Build the test executable along with the source files
add_executable(run_tests 
    polynomsolver_tests.cpp
    polynom_tests.cpp
    ../src/PolynomSolver.cpp
    ../src/Polynom.cpp
    ../src/Constants.h
)

# Include directories for header files
target_include_directories(run_tests PRIVATE ../src)

target_link_libraries(run_tests PRIVATE 
    GTest::gtest_main 
    GTest::gmock_main
)

# Register the test
add_test(NAME WhitespaceTests COMMAND run_tests)
