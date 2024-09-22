cmake_minimum_required(VERSION 3.5)
project(RTOS_KERNEL C)

########################################################################################################################
## OPTIONS
option(OS_MEMORY_USE_TLSF "Use TLSF Memory Pool" ON)

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
## DEPENDENCIES
if(NOT TARGET RTOS_COMPILER)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Compiler ${CMAKE_CURRENT_BINARY_DIR}/Compiler)
endif ()
target_link_libraries(${PROJECT_NAME} PUBLIC RTOS_COMPILER)

if(NOT TARGET RTOS_CPU)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../CPU ${CMAKE_CURRENT_BINARY_DIR}/CPU)
endif ()
target_link_libraries(${PROJECT_NAME} PUBLIC RTOS_CPU)


if(OS_MEMORY_USE_TLSF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Pub/TLSF-2.4.6  ${CMAKE_CURRENT_BINARY_DIR}/TLSF)
    target_link_libraries(${PROJECT_NAME} PUBLIC TLSF)
endif ()