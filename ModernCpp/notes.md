# Class Notes

## Compilation behind the escenes

1. Pre-process: copy pasting libraries.

    ```bash
    g++ -E main.cpp > main.i
    ```

2. Compile: Translation to assembly.

    ```bash

    g++ -S main.cpp > main.i
    ```

3. Assembler: Creates object file (binary).

    ```bash
    
    g++ -E main.cpp > main.i
    ```

4. *Linker: Adds libraries.

    ```bash
    g++ -E main.cpp > main.i
    ```

## Compilation flags (-)

 Manages features of C++:

- std=c++17, ...

Allows:

- Optimization:
  - O0, O2, O3...
  - Os (Optimizes for size and efficiency)
- Debugging symbols
  - g
- Warnings as errors:
  - Wall
  - Wextra
  - Werror

> Check [Compiler Explorer](https://godbolt.org/) to see how compilation flags affect the assembly code.

## Header/Source separation

1. Declaration: .hpp

    > Add `#pragma once` to header file to include just once.

2. Definition: .cpp

3. Calling: main.cpp

## Linking

Adding library to file. First we need a library header file and the compiled library (.a)

## Types of libraries

### Static

- lib*.a
- Binary copied into executable (increases size).
- Much faster.
- Present at *compile* time.

> The compiler checks the library! Its better for smaller size projects.

### Dynamic (shared)

- lib*.so
- Symbolic link between binary of library and executable.
- Small executable and slower.
- The originally library needs to be there.
- Present at *runtime* time.

> The compiler doesn't check it! It can't help you, but it helps if the project is big and complex. The downside is that you cannot guarantee it will work on a different machine.

## How to build libraries

1. Compile lib.
2. ...

Look at class slides!!!

## CMAKE

Simple static library added to a main file.

```cmake
cmake_minimum_required(VERSION 3.1)  # Mandatory
project(first_project)  # Name

# Create library
add_library(lib STATIC src/lib.cpp)  # SHARED -> Dynamic

# Define library C++ standard
target_compile_features(lib PRIVATE cxx_std_17)
# PRIVATE means will not propagate the feature

# Tell cmake where to look for *.hpp, *.h files
target_include_directories(lib PUBLIC include/)

# Define compiler options
target_compile_options(lib PRIVATE -Wall -Werror)

# Add executable main
add_executable(main src/main.cpp)
target_link_libraries(main lib)
```

> One `cmakelists.txt` file shouldn't handle everything, We should split it into chunks -> Easier to debug.

> Target oriented CMAKE is the new kid on the block.

```cmake
# REQUIRED -> Mandatory pacakge
# HINTS -> DIRECTORY
find_package(library REQUIRED HINTS ${PROJECT_SOURCE_DIR}/)
```

The `cmake` file inside the library contains the information needed by `CMakeLists.txt` to add it to your project.

`${CMAKE_CURRENT_SOURCE_DIR}` Will point to the current folder where the `CMakeLists.txt` is.

The name you pick for a library or executable is called a *target*. You should always keep it in mind when linking. You can find them out usually in the `LibraryTargets.cmake` file.

To compile: `cmake -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=1 && cmake --build build`