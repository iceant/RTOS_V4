cmake_minimum_required(VERSION 3.5)
project(RTOS_CPU C)
enable_language(ASM)


########################################################################################################################
## OPTIONS
if(NOT DEFINED RTOS_CPU_MODEL)
    message(FATAL_ERROR "[${PROJECT_NAME}] Missing `RTOS_CPU_MODEL` VARIABLE")
endif ()

########################################################################################################################
## TARGET
add_library(${PROJECT_NAME} "")

########################################################################################################################
## SOURCES
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
foreach (item IN LISTS SOURCES)
    message(STATUS "[${PROJECT_NAME}] SOURCES: ${item}")
endforeach ()
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

########################################################################################################################
## CPU MODEL SOURCES
set(CPU_MODEL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${RTOS_CPU_MODEL})
message(STATUS "[${PROJECT_NAME}] CPU_MODEL_DIR=${CPU_MODEL_DIR}")
if(EXISTS ${CPU_MODEL_DIR})
    file(GLOB CPU_MODEL_SOURCES ${CPU_MODEL_DIR}/*.c)
    foreach (item IN LISTS CPU_MODEL_SOURCES)
        message(STATUS "[${PROJECT_NAME}] CPU_MODEL_SOURCES: ${item}")
    endforeach ()
endif ()

target_sources(${PROJECT_NAME} PUBLIC ${CPU_MODEL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CPU_MODEL_DIR})

########################################################################################################################
## COMPILER SPECIFIED SOURCES
set(COMPILER_SOURCE_DIR ${CPU_MODEL_DIR}/${CMAKE_C_COMPILER_ID})
message(STATUS "[${PROJECT_NAME}] COMPILER_SOURCE_DIR=${COMPILER_SOURCE_DIR}")
if(EXISTS ${COMPILER_SOURCE_DIR})
    file(GLOB COMPILER_SOURCES ${COMPILER_SOURCE_DIR}/*.c)
    foreach (item IN LISTS COMPILER_SOURCES)
        message(STATUS "[${PROJECT_NAME}] COMPILER_SOURCES: ${item}")
    endforeach ()
    target_include_directories(${PROJECT_NAME} PUBLIC ${COMPILER_SOURCE_DIR})
endif ()

target_sources(${PROJECT_NAME} PUBLIC ${COMPILER_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${COMPILER_SOURCE_DIR})

########################################################################################################################
## DEPENDENCIES
if(NOT TARGET RTOS_COMPILER)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Compiler ${CMAKE_CURRENT_BINARY_DIR}/Compiler)
endif ()
target_link_libraries(${PROJECT_NAME} PUBLIC RTOS_COMPILER)
