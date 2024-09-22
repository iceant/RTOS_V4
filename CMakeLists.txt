cmake_minimum_required(VERSION 3.28)
project(RTOS_V4 C)

set(CMAKE_C_STANDARD 11)

if(NOT TARGET RTOS_COMPILER)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Compiler)
endif ()

if(NOT TARGET RTOS_CPU)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CPU)
endif ()

if(NOT TARGET RTOS_KERNEL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Kernel)
endif ()

if(NOT TARGET RTOS_SDK)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDK)
endif ()
