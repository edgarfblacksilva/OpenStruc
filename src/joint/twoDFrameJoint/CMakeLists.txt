# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:

set(twoDFrameJoint_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/twoDFrameJoint.cpp    
    PARENT_SCOPE
   )
