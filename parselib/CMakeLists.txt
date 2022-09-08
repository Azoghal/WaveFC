add_library(parselib parser.cxx)

add_dependencies(parselib wfclib)
target_link_libraries(parselib wfclib) #link library where target is created
target_include_directories(
    parselib PUBLIC 
    "${PROJECT_SOURCE_DIR}/wfclib"
)
