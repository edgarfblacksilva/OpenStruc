# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:

add_subdirectory(threeDFrameJoint)
add_subdirectory(threeDTrussJoint)
add_subdirectory(twoDFrameJoint)
add_subdirectory(twoDTrussJoint)
add_subdirectory(gridJoint)


set(joint_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/joint.cpp
    ${threeDFrameJoint_Src}  
    ${threeDTrussJoint_Src}
    ${twoDFrameJoint_Src}
    ${twoDTrussJoint_Src} 
    ${gridJoint_Src}
    PARENT_SCOPE
   )
