# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:

set(threeDFrameElement_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/threeDFrameElement.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/printElementPrimaryForces.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/mult6.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/mult4.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/defineSectionProperties.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/setElementStiffnessFactors.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/setElementLengthAndRotation.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/setSectionProperties.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/getLocalStiffnessMatrix.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/getGlobalStiffnessMatrix.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/applyTempGradients.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/finishApplingPrimaryForces.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/applyUniformLoads.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/applyConcentratedLoads.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/applyConcentratedMoment.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/applyUniformTorsion.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/applyLinVarLoads.cpp 
    PARENT_SCOPE
   )
