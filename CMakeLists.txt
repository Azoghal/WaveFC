cmake_minimum_required(VERSION 3.10)

project(cpp_prep VERSION 1.0 LANGUAGES CXX)

configure_file(prep_config.h.in prep_config.h)

add_subdirectory(hwlib)

add_executable(cpp_prep main.cxx)

target_link_libraries(cpp_prep PUBLIC hwlib)

target_include_directories(
    cpp_prep PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/hwlib"
)

install(TARGETS cpp_prep DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/prep_config.h" DESTINATION include) 