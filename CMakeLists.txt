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
elseif ( CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM" )
    set(CMAKE_CXX_COMPILER "icpx")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -fvectorize  -qopt-report-file=stderr -qopt-report=max  -xCORE-AVX2")
    #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -qopt-report=5 -qopt-report-phase=vec ")
elseif ( CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC" )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Minform=inform  -Minfo=all -Mvect=simd ")
    #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Minform=inform  -Mnodepchk -Minfo=all -Mvect=simd -tp=px ")
endif ( )
## end of adding the following lines while cleaning the code

find_package(Python3 COMPONENTS Interpreter Development )
find_package(Python 3.9 REQUIRED COMPONENTS Interpreter Development.Module NumPy)


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
include_directories(${Python3_INCLUDE_DIRS}) 
include_directories(${Python_NumPy_INCLUDE_DIRS}) 

#include_directories("../myheaders")

ADD_LIBRARY( ObjectScan STATIC ${ObjScan_Src} )
#ADD_LIBRARY( ObjectScan SHARED ${ObjScan_Src} )

add_executable(${PROJECTNAME} ${openStruc_Src} )
target_link_libraries(${PROJECTNAME}  ObjectScan  ${Python3_LIBRARIES}  ${CMAKE_EXE_LINKER_FLAGS})

