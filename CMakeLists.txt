cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(WaveFC VERSION 1.0 LANGUAGES CXX)

configure_file(prep_config.h.in prep_config.h)

add_subdirectory(rendlib)
add_subdirectory(wfclib)
add_subdirectory(parselib)

add_executable(WaveFC main.cxx)

target_link_libraries(WaveFC PUBLIC rendlib wfclib parselib)

target_include_directories(
    WaveFC PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/rendlib"
    "${PROJECT_SOURCE_DIR}/wfclib"
    "${PROJECT_SOURCE_DIR}/parselib"
)

install(TARGETS WaveFC DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/prep_config.h" DESTINATION include)