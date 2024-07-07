add_executable(main main.cpp)  # Generates a binary with the main function inside
target_link_libraries(main PRIVATE my_vector)  # Link against library TARGET PRIVATE/PUBLIC LIBRARY
target_compile_features(main PRIVATE cxx_std_17)