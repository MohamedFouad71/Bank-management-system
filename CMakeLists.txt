cmake_minimum_required(VERSION 3.10)
project(BankManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(BankApp ${SOURCES})

# To support colors in terminal on Windows
if (WIN32)
    add_definitions(-DTERM_COLOR_WIN)
endif()
