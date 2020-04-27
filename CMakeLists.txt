cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)

# Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

## Void_Run
file(GLOB_RECURSE SOURCES void_run/*.cpp void_run/*.h)
add_executable(void_run ${SOURCES})
target_include_directories(void_run SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(void_run lib_engine)
set_target_properties(void_run PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
add_dependencies(void_run copy_resources)

## Ecm
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

## engine
file(GLOB_RECURSE SOURCE_FILES lib_engine/*.cpp lib_engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES}  ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/lib_engine/")
target_link_libraries(lib_engine lib_maths lib_ecm sfml-graphics sfml-audio)

