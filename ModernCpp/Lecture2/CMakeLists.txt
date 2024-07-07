cmake_minimum_required(VERSION 3.1)
project(first_project)

# Create library libtools
add_library(tools SHARED src/tools.cpp)

# Define library C++ standard
target_compile_features(tools PRIVATE cxx_std_17)

# Tell CMake where to look for *.hpp, *.h files
target_include_directories(tools PUBLIC include/)

# Define compiler options, target based
target_compile_options(tools PRIVATE -Wall -Werror)

# Add executable main
add_executable(main src/main.cpp)
target_link_libraries(main tools)
