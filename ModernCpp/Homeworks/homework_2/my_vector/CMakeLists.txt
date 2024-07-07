add_library(my_vector STATIC my_vector.cpp)  # BINARY TYPE CPP
target_include_directories(my_vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)  # Tells where to look for header files
target_compile_features(my_vector PRIVATE cxx_std_17)  # Which standard features to use