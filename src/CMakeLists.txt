# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:

add_subdirectory(main)
add_subdirectory(joint)
add_subdirectory(element)
add_subdirectory(openStruc)

set(openStruc_Src
    #${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${main_Src}
#    
    #${CMAKE_CURRENT_SOURCE_DIR}/OpenStruc.cpp
    ${openStruc_Src}
#    
#    ${CMAKE_CURRENT_SOURCE_DIR}/joint.cpp
    ${joint_Src}
#    
    #${CMAKE_CURRENT_SOURCE_DIR}/element.cpp
    ${elementy_Src}
    
#    ${CMAKE_CURRENT_SOURCE_DIR}/
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    PARENT_SCOPE
   )
