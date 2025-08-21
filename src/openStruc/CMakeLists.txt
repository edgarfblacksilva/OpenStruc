# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:

set(openStruc_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/assembleGlobalStifnessMatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/combineLoadCases.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/defineElements.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/driver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/finishLoadVector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/formLeftColumn.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/getNodalLoads.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/getPrimaryForcesDueToDisplaecments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/getPrimaryForcesDueToGlobalTemp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/getPrimaryForcesDueToLoads.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/getTitle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/header.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/openStruc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printElementsSolution.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printJointDisplacements.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printJointsSolution.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printStrucData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readCoordinatesAndConstraints.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readIncidences.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readLoadCases.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readMaterials.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readSectionTypes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setBasicData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setElementsForcesBinaryFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setErrorMassages.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setStructureType.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setWorkingFileName.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/solveDisplacements.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/welcomeBanner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/plotStruc.cpp
    PARENT_SCOPE
   )
