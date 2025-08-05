# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:


set(ObjScan_Src
#    ${CMAKE_CURRENT_SOURCE_DIR}/scandemo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ObjectScan.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/trlist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trxlst.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sizlst.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sep.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/name.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/isstring.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/endstr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scan_contents.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backsp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toLowerStr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/matchs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/matchs_exact.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/numi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/integr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/floatn.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/numf.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/numd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/updateInputFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setInputFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/in_from_stdin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setOutputFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out_to_stdout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scanDebug.cpp
    PARENT_SCOPE
   )
