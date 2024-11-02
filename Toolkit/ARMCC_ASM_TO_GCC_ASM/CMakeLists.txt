cmake_minimum_required(VERSION 3.5)
project(ARMCC_ASM_TO_GCC_ASM C)

add_executable(${PROJECT_NAME} "")
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


