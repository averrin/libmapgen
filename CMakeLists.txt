cmake_minimum_required(VERSION 2.8.6)
project (generator)
set (CMAKE_BUILD_TYPE Debug)

#include *.h files under include folder and  
#the project's output folder e.g. Debug
include_directories (include ${PROJECT_BINARY_DIR})

#compile all *.cpp source files under src folder
file (GLOB SOURCES "src/*.cpp")

#output library as generator.*

#output library export file *.lib and
#output macro definitions include file
include (GenerateExportHeader)
add_library(generator SHARED ${SOURCES})
GENERATE_EXPORT_HEADER (generator
    BASE_NAME generator
    EXPORT_MACRO_NAME generator_EXPORT
    EXPORT_FILE_NAME generator_Export.h
    STATIC_DEFINE generator_BUILT_AS_STATIC
)
