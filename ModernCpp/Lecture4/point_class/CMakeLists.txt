# Header-only library
add_library(point_class INTERFACE)

target_include_directories(point_class INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_features(point_class INTERFACE cxx_std_17)  # Which standard features to use