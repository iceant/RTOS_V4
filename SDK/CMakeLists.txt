cmake_minimum_required(VERSION 3.5)
project(RTOS_SDK C)

########################################################################################################################
## OPTIONS
option(RTOS_SDK_INCLUDE_TEST "Enable Test" OFF)
option(RTOS_SDK_ENABLE_RTOS "Enable RTOS" OFF)


########################################################################################################################
## TARGET
add_library(${PROJECT_NAME} "")

########################################################################################################################
## SOURCES
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
list(FILTER SOURCES EXCLUDE REGEX \\.t\\.c)
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


if(RTOS_SDK_ENABLE_RTOS)
    add_definitions(-DRTOS_SDK_ENABLE_RTOS=1)
    if(NOT TARGET RTOS_KERNEL)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Kernel ${CMAKE_CURRENT_BINARY_DIR}/Kernel)
    endif ()
    target_link_libraries(${PROJECT_NAME} PUBLIC RTOS_KERNEL)
endif ()

########################################################################################################################
## TEST
if(RTOS_SDK_INCLUDE_TEST)
file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.t.c)
foreach (item IN LISTS TEST_SOURCES)
    get_filename_component(TestUnit ${item} NAME_WLE)
    message(STATUS "[${PROJECT_NAME}] TEST_SOURCES: ${TestUnit} - ${item}")
    add_executable(${TestUnit} ${item})
    target_link_libraries(${TestUnit} PRIVATE ${PROJECT_NAME})
endforeach ()
endif ()