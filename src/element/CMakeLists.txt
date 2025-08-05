# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:

add_subdirectory(threeDFrameElement)
add_subdirectory(threeDTrussElement)
add_subdirectory(twoDFrameElement)
add_subdirectory(twoDTrussElement)
add_subdirectory(gridElement)

set(elementy_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/element.cpp
    ${threeDFrameElement_Src}  
    ${threeDTrussElement_Src}
    ${twoDFrameElement_Src}
    ${twoDTrussElement_Src} 
    ${gridElement_Src}
    PARENT_SCOPE
   )
