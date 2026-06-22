cmake_minimum_required(VERSION 3.14)
project(PolynomSolver)

# Policies
cmake_policy(SET CMP0092 NEW)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

enable_testing()

# Dependencies
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Executable
add_executable(polynomsolver_app
    #src/PolynomSolver.cpp
    src/Polynom.cpp
    src/main.cpp
 "src/Constans.h")

add_subdirectory(tests)