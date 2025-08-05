cmake_minimum_required(VERSION 3.16)

set(PROJECTNAME "OpenStruc")

## set appropriately the following line to create a Double Precision version
set(DOUBLE_PRECISION ON)

project(${PROJECTNAME} CXX)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD ON)
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

## adding the following lines while cleaning the code
    MESSAGE( STATUS "CMAKE_CXX_COMPILER_ID: "         ${CMAKE_CXX_COMPILER_ID} )
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
   #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -ftree-vectorize -fopt-info -ffast-math -mavx2 ")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -ftree-vectorize -fopt-info -ffast-math ")
    #set(CMAKE_EXE_LINKER_FLAGS "-lm" )
elseif ( CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM" )
    set(CMAKE_CXX_COMPILER "icpx")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -fvectorize  -qopt-report-file=stderr -qopt-report=max  -xCORE-AVX2")
    #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -qopt-report=5 -qopt-report-phase=vec ")
elseif ( CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC" )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Minform=inform  -Minfo=all -Mvect=simd ")
    #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Minform=inform  -Mnodepchk -Minfo=all -Mvect=simd -tp=px ")
endif ( )
## end of adding the following lines while cleaning the code


#if (DOUBLE_PRECISION)
#    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DDOUBLE")
#endif()


add_subdirectory(src)
add_subdirectory(ObjectScan/src ObjectScanLibDir)
include_directories("src/include")
include_directories("src/openStruc/include")
include_directories("ObjectScan/src/include")
include_directories("src/element/include")
include_directories("src/element/threeDFrameElement/include")
include_directories("src/element/twoDFrameElement/include")
include_directories("src/element/threeDTrussElement/include")
include_directories("src/element/twoDTrussElement/include")
include_directories("src/element/gridElement/include")
include_directories("src/joint/include")
include_directories("src/joint/threeDFrameJoint/include")
include_directories("src/joint/twoDFrameJoint/include")
include_directories("src/joint/threeDTrussJoint/include")
include_directories("src/joint/twoDTrussJoint/include")
include_directories("src/joint/gridJoint/include")
#include_directories("../myheaders")

ADD_LIBRARY( ObjectScan STATIC ${ObjScan_Src} )
#ADD_LIBRARY( ObjectScan SHARED ${ObjScan_Src} )

###########################################################################################
#
# https://stackoverflow.com/questions/4283731/plotting-package-for-c
# sudo apt-get install libgnuplot-iostream-dev
#
ADD_LIBRARY( gnuplotIostream STATIC ${ObjScan_Src} )
set(GNUPLOT_IOSTREAM "-lboost_iostreams -lboost_system -lboost_filesystem")
###########################################################################################

add_executable(${PROJECTNAME} ${openStruc_Src} )
target_link_libraries(${PROJECTNAME}  ObjectScan  ${GNUPLOT_IOSTREAM} ${CMAKE_EXE_LINKER_FLAGS})


############### Debug messages ####################
#MESSAGE( STATUS "CMAKE_BINARY_DIR: "            ${CMAKE_BINARY_DIR} )
#MESSAGE( STATUS "CMAKE_C_COMPILER_ID: "         ${CMAKE_C_COMPILER_ID} )
#MESSAGE( STATUS "CMAKE_CXX_FLAGS: "               ${CMAKE_CXX_FLAGS} )
#MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: "    ${CMAKE_CURRENT_SOURCE_DIR} )
########### end of Debug messages #################
