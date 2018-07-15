cmake_minimum_required(VERSION 2.8.6)
project (generator)
set (CMAKE_BUILD_TYPE Debug)

#include *.h files under include folder and  
#the project's output folder e.g. Debug
include_directories (include ${PROJECT_SOURCE_DIR}
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/include/Voronoi/include"
)
file(GLOB VLIB_SOURCE "${PROJECT_SOURCE_DIR}/include/Voronoi/src/*.cpp" "${PROJECT_SOURCE_DIR}/include/Voronoi/include/*.h")
add_library(voronoi ${VLIB_SOURCE})

#compile all *.cpp source files under src folder
file (GLOB SOURCES "src/*.cpp" "include/*.cpp")

#output library as generator.*

#output library export file *.lib and
#output macro definitions include file
include (GenerateExportHeader)
add_library(generator SHARED ${SOURCES})

target_link_libraries(generator voronoi "${PROJECT_SOURCE_DIR}/include/libnoise.lib")
GENERATE_EXPORT_HEADER (generator
    BASE_NAME generator
    EXPORT_MACRO_NAME generator_EXPORT
    EXPORT_FILE_NAME generator_Export.h
    STATIC_DEFINE generator_BUILT_AS_STATIC
)
