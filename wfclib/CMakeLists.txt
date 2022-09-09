add_library(wfclib wave_function_collapse.cxx tile.cxx constraints.cxx parser.cxx)

add_dependencies(wfclib rendlib)
target_link_libraries(wfclib rendlib) #link library where target is created
target_include_directories(
    wfclib PUBLIC 
    "${PROJECT_SOURCE_DIR}/rendlib"
)

