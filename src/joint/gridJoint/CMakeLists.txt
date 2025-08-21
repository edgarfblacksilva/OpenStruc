# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:

set(gridJoint_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/gridJoint.cpp    
    PARENT_SCOPE
   )
