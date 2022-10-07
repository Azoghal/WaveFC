cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(WaveFC VERSION 1.0 LANGUAGES CXX)

configure_file(prep_config.h.in prep_config.h)
configure_file("${PROJECT_SOURCE_DIR}/inputs/file.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/inputs/file_2.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/inputs/file_3.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/inputs/file_4.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/inputs/constraints.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/inputs/constraints_2.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#file(GLOB "${PROJECT_SOURCE_DIR}/inputs" "*.txt" CONFIGURE_DEPENDS "*.hxx" "*.cxx")


add_subdirectory(rendlib)
add_subdirectory(wfclib)

add_executable(WaveFC main.cxx)

target_link_libraries(WaveFC PUBLIC rendlib wfclib)

target_include_directories(
    WaveFC PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/rendlib"
    "${PROJECT_SOURCE_DIR}/wfclib"
)

install(TARGETS WaveFC DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/prep_config.h" DESTINATION include)