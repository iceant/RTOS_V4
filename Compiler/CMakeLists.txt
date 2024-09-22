cmake_minimum_required(VERSION 3.5)
project(RTOS_COMPILER C)

########################################################################################################################
## TARGET
add_library(${PROJECT_NAME} "")

########################################################################################################################
## COMPILER SPECIFIED SOURCES
set(COMPILER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_C_COMPILER_ID})
if(EXISTS ${COMPILER_SOURCE_DIR})
    file(GLOB COMPILER_SOURCES ${COMPILER_SOURCE_DIR}/*.c)
    foreach (item IN LISTS COMPILER_SOURCES)
        message(STATUS "[${PROJECT_NAME}] COMPILER_SOURCES: ${item}")
    endforeach ()
endif ()

target_sources(${PROJECT_NAME} PUBLIC ${COMPILER_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${COMPILER_SOURCE_DIR})
