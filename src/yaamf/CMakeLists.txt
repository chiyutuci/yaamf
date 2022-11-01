set(YAAMF_SOURCE main.cpp mathtypes.cpp yaamf.cpp tools.cpp integral.cpp)

add_executable(yaamf ${YAAMF_SOURCE})

target_include_directories(yaamf PUBLIC ${CMAKE_SOURCE_DIR}/src)

find_library(FLINT_LIBRARY flint)
if(NOT FLINT_LIBRARY)
    message(FATAL_ERROR "flint library not found.")
endif()

find_library(YAML_LIBRARY yaml-cpp)
if(NOT YAML_LIBRARY)
    message(FATAL_ERROR "yaml-cpp library not found.")
endif()

target_link_libraries(yaamf ${FLINT_LIBRARY} ${YAML_LIBRARY})