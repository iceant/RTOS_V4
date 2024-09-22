cmake_minimum_required(VERSION 3.5)
project(TLSF C)
set(PROJECT_VERSION_MAJOR 2)
set(PROJECT_VERSION_MINOR 4)
set(PROJECT_VERSION_TWEAK 2)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_TWEAK})

########################################################################################################################
## OPTIONS
option(TLSF_USE_PRINTF "USE_PRINTF" ON)
option(TLSF_USE_LOCKS "TLSF_USE_LOCKS" OFF)
option(TLSF_STATISTIC "TLSF_STATISTIC" OFF)
option(TLSF_USE_MMAP "USE_MMAP" OFF)
option(TLSF_USE_SBRK "USE_SBRK" OFF)

########################################################################################################################
## DEFINITIONS
if(TLSF_USE_PRINTF)
add_definitions(-DUSE_PRINTF=1)
endif ()

if(TLSF_USE_LOCKS)
    add_definitions(-DTLSF_USE_LOCKS=1)
endif ()

if(TLSF_STATISTIC)
    add_definitions(-DTLSF_STATISTIC=1)
endif ()

if(TLSF_USE_MMAP)
    add_definitions(-DUSE_MMAP=1)
endif ()

if(TLSF_USE_SBRK)
    add_definitions(-DUSE_SBRK=1)
endif ()

########################################################################################################################
## SOURCES

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_library(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)